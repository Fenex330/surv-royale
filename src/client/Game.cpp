#include "headers.hpp"

sf::Font Game::font;
std::string Game::nickname = "";
bool Game::isGameRunning = false;
bool Game::quit = false;
long Game::tar_size = 0;
char *Game::tarFile = nullptr;

Game::Game() : window (sf::VideoMode (surv::VIEW_DIM_X, surv::VIEW_DIM_Y), "SurvRoyale " + std::string(GAME_VERSION), sf::Style::Close),
               crosshair_distance (0.0),
               slot (1),
               fps (0),
               ping (0),
               ping_avg (0),
               ping_count (0)
{
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    window.setMouseCursorVisible(true);

    ImGui::SFML::Init(window);
    FILE *f = std::fopen(GAMEDATA_PATH, "rb");

    std::fseek(f, 0, SEEK_END);
    tar_size = std::ftell(f);
    std::fseek(f, 0, SEEK_SET);

    tarFile = (char*)std::malloc(tar_size + 1);
    [[maybe_unused]] std::size_t temp = std::fread(tarFile, 1, tar_size, f);
    std::fclose(f);

    Game::loadAsset(font, "GameData/fonts/RobotoCondensed-Regular.ttf");
    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);

    Game::loadAsset(crosshair_texture, "GameData/graphics/crosshairs/11.png");
    crosshair.setTexture(crosshair_texture);
    crosshair.setOrigin(crosshair.getLocalBounds().width * 0.5, crosshair.getLocalBounds().height * 0.5);
    crosshair.setScale(0.5, 0.5);

    UDPsocket.setBlocking(false);
    TCPsocket.setBlocking(false);

    if (fs::exists(ID_PATH))
    {
        unsigned short local_port;
        std::ifstream id (ID_PATH);
        id >> ID >> local_port;

        if (UDPsocket.bind(local_port) != sf::Socket::Done)
            quit = true;
    }
    else
    {
        if (UDPsocket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
            quit = true;

        generateID();
    }
}

Game::~Game()
{
    free(tarFile);
    ImGui::SFML::Shutdown();

    if (!isGameRunning)
        fs::remove(ID_PATH);
}

void Game::play()
{
    isGameRunning = true;
    window.setMouseCursorVisible(false);
    players.insert({nickname, Player()});
    players.at(nickname).init(nickname);
}

void Game::run()
{
    while (window.isOpen() && !quit) // main game loop
    {
        sf::Event event;

        while (window.pollEvent(event)) // event handler loop
        {
            ImGui::SFML::ProcessEvent(window, event);

            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
        }

        ImGui::SFML::Update(window, imguiClock.restart());
        imguiMapUI();
        window.clear();
        draw();
        ImGui::SFML::Render(window);
        window.display();
        listen();

        if (window.hasFocus() && isGameRunning)
        {
            float crossX = sf::Mouse::getPosition(window).x - surv::VIEW_DIM_X / 2.0 + players.at(nickname).sprite.getPosition().x;
            float crossY = sf::Mouse::getPosition(window).y - surv::VIEW_DIM_Y / 2.0 + players.at(nickname).sprite.getPosition().y;
            crosshair_distance = surv::getDistance(crossX, players.at(nickname).sprite.getPosition().x, crossY, players.at(nickname).sprite.getPosition().y);
            crosshair.setPosition(crossX, crossY);
            text.setPosition(players.at(nickname).sprite.getPosition() - sf::Vector2f(surv::VIEW_DIM_X / 2, surv::VIEW_DIM_Y / 2));
            text.setString("fps: " + std::to_string(fps) + "    ping: " + std::to_string(ping));
            window.setView(players.at(nickname).view);
            sendPlayerInput();
            countFpsAndPing();
        }
    }
}

void Game::imguiMapUI()
{
    if (isGameRunning)
        return;

    static char buf1[64] = "";
    static char buf2[64] = "127.0.0.1";
    static char buf3[64] = "7777";
    static char buf4[64] = "";

    ImGui::Begin("Main Menu");
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s", join_error.c_str());
    ImGui::InputTextWithHint("nickname", "no spaces allowed", buf1, 64);
    ImGui::InputText("address", buf2, 64);
    ImGui::InputText("port", buf3, 64);
    ImGui::InputTextWithHint("password", "leave empty if none", buf4, 64, ImGuiInputTextFlags_Password);

    if (ImGui::Button("PLAY!"))
    {
        join_error = "";
        nickname = std::string(buf1);
        server_address = std::string(buf2);
        server_port = std::stoi(std::string(buf3));
        password = std::string(buf4);
        sendJoinRequest();
    }

    if (ImGui::Button("QUIT"))
        quit = true;

    ImGui::End();
}

void Game::draw()
{
    if (!isGameRunning)
        return;

    for (const auto& n : players)
    {
        window.draw(n.second.sprite);
        window.draw(n.second.nick);
    }

    window.draw(crosshair);
    window.draw(text);
}

void Game::generateID()
{
    ID = "";

    for (int i = 0; i < 20; i++)
        ID.append(std::to_string(surv::getRandom(0, 9)));

    std::ofstream id (ID_PATH);
    id << ID << " " << UDPsocket.getLocalPort() << endl;
}

void Game::countFpsAndPing()
{
    static int i = 0;
    sf::Time elapsed = fpsClock.getElapsedTime();
    i++;

    if (elapsed > sf::seconds(1))
    {
        fps = i;
        ping = (ping_avg / ping_count) % 5000;
        i = 0;
        ping_avg = 0;
        ping_count = 0;
        fpsClock.restart();
    }
}

void Game::send()
{
    sf::Time elapsed = udpClock.getElapsedTime();

    if (elapsed < sf::milliseconds(surv::SEND_DELAY))
        return;

    udpClock.restart();
    assert(packet.getDataSize() <= sf::UdpSocket::MaxDatagramSize);
    if (UDPsocket.send(packet, server_address, server_port) != sf::Socket::Done) {}
    packet.clear();
}

void Game::sendJoinRequest()
{
    packet << static_cast<sf::Uint8>(NetCodes::JoinRequest) << nickname << ID << password << std::string(GAME_VERSION);
    send();
}

void Game::sendPlayerInput()
{
    auto [x, y] = mainPlayerInputMovement();
    auto [R, L] = mainPlayerInputMouse();
    double rotation = mainPlayerInputRotation();
    mainPlayerInputSlot();

    packet << static_cast<sf::Uint8>(NetCodes::PlayerInput) << nickname << ID << x << y << R << L << rotation << slot << crosshair_distance;
    send();
}

void Game::listen()
{
    sf::IpAddress remote_address;
    unsigned short remote_port; // unused placeholder

    if (UDPsocket.receive(packet, remote_address, remote_port) != sf::Socket::Done)
        return;

    if (remote_address != server_address)
        return;

    ping_count++;
    ping_avg += pingClock.restart().asMilliseconds();
    sf::Uint8 netcode_raw;
    packet >> netcode_raw;
    NetCodes netcode = static_cast<NetCodes>(netcode_raw);

    switch (netcode)
    {
        case NetCodes::JoinError:
            receiveJoinError();
            break;

        case NetCodes::PlayersList:
            receivePlayersList();
            break;

        case NetCodes::ProjectilesList:
            receiveProjectilesList();
            break;

        case NetCodes::ObjectsList:
            receiveObjectsList();
            break;

        case NetCodes::GameState:
            receiveGameState();
            break;

        default:
            break;
    }

    packet.clear();
}

void Game::receiveJoinError()
{
    std::string version;
    sf::Uint8 errorcode_raw;
    packet >> errorcode_raw;
    ErrorCodes errorcode = static_cast<ErrorCodes>(errorcode_raw);

    switch (errorcode)
    {
        case ErrorCodes::MapFull:
            join_error = "game is full\ntry again later";
            server_port++;
            sendJoinRequest();
            break;

        case ErrorCodes::InvalidVersion:
            packet >> version;
            join_error = "versions do not match\nplease upgrade or downgrade your client\nserver version is " + version;
            break;

        case ErrorCodes::InvalidPassword:
            join_error = "invalid password";
            break;

        case ErrorCodes::NicknameExists:
            join_error = "nickname is invalid or already exists";
            break;

        case ErrorCodes::Kick:
            isGameRunning = false;
            join_error = "you have been kicked from this match";
            break;

        case ErrorCodes::IpBan:
            isGameRunning = false;
            join_error = "you have been banned from this server";
            break;

        default:
            break;
    }
}

void Game::receivePlayersList()
{
    if (!isGameRunning)
        play();

    std::string nick;
    sf::Int16 x, y;
    double rotation;

    while (packet >> nick >> x >> y >> rotation)
    {
        if (players.find(nick) == players.end())
        {
            players.insert({nick, Player()});
            players.at(nick).init(nick);
        }

        players.at(nick).setPosition(x, -y);
        players.at(nick).setRotation(rotation + surv::PI / 2.0);
    }
}

void Game::receiveProjectilesList()
{
    //
}

void Game::receiveObjectsList()
{
    //
}

void Game::receiveGameState()
{
    //
}

std::pair<sf::Int8, sf::Int8> Game::mainPlayerInputMovement()
{
    sf::Int8 x = 0;
    sf::Int8 y = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) y++;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) x--;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) y--;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) x++;

    return std::make_pair(x, y);
}

std::pair<bool, bool> Game::mainPlayerInputMouse()
{
    return std::make_pair(sf::Mouse::isButtonPressed(sf::Mouse::Right),
                          sf::Mouse::isButtonPressed(sf::Mouse::Left));
}

double Game::mainPlayerInputRotation()
{
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
    return std::atan2(mouse_position.y - surv::VIEW_DIM_Y / 2.0, mouse_position.x - surv::VIEW_DIM_X / 2.0) + surv::PI;
}

void Game::mainPlayerInputSlot()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) slot = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) slot = 2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) slot = 3;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) slot = 4;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) slot = 5;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) slot = 6;
}
