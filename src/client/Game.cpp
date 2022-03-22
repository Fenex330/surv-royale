#include "headers.hpp"

bool Game::isGameRunning = false;
bool Game::quit = false;
long Game::tar_size = 0;
char *Game::tarFile = nullptr;

Game::Game() : window (sf::VideoMode (surv::VIEW_DIM_X, surv::VIEW_DIM_Y), "Main Menu", sf::Style::Close)
{
    std::atexit(Game::cleanup);

    server_port = surv::DEFAULT_PORT;
    slot = 1;

    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    window.setMouseCursorVisible(true);

    ImGui::SFML::Init(window);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    FILE *f = fopen(GAMEDATA_PATH, "rb");

    fseek(f, 0, SEEK_END);
    tar_size = ftell(f);
    fseek(f, 0, SEEK_SET);

    tarFile = (char*)malloc(tar_size + 1);
    fread(tarFile, 1, tar_size, f);
    fclose(f);

    Game::loadAsset(crosshair_texture, "GameData/graphics/crosshairs/11.png");
    crosshair.setTexture(crosshair_texture);
    crosshair.setOrigin(crosshair.getLocalBounds().width * 0.5, crosshair.getLocalBounds().height * 0.5);
    crosshair.setScale(0.5, 0.5);

    UDPsocket.setBlocking(false);
    TCPsocket.setBlocking(false);

    if (UDPsocket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
        std::exit(1);

    //local_port = UDPsocket.getLocalPort();
}

Game::~Game()
{
    Game::cleanup();
}

void Game::play()
{
    isGameRunning = true;
    window.setMouseCursorVisible(false);
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

        ImGui::SFML::Update(window, deltaClock.restart());
        imguiMapUI();

        window.clear();
        //window.setView(main_player.view);
        draw();
        ImGui::SFML::Render(window);
        window.display();

        /*if (window.hasFocus() && isGameRunning)
        {
            float crossX = sf::Mouse::getPosition(window).x - surv::VIEW_DIM_X / 2.0 + main_player.sprite.getPosition().x;
            float crossY = sf::Mouse::getPosition(window).y - surv::VIEW_DIM_Y / 2.0 + main_player.sprite.getPosition().y;
            crosshair_distance = getDistance(crossX, main_player.sprite.getPosition().x, crossY, main_player.sprite.getPosition().y);
            crosshair.setPosition(crossX, crossY);
        }*/
    }
}

void Game::imguiMapUI()
{
    static char buf1[64] = "";
    static char buf2[64] = "";
    static char buf3[64] = "";

    if (isGameRunning)
        return;

    ImGui::Begin("Main Menu");
    //ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 0.0f), error.c_str());
    ImGui::InputText("nickname", buf1, 64);
    ImGui::InputText("server address", buf2, 64);
    ImGui::InputTextWithHint("password", "leave empty if none", buf3, 64, ImGuiInputTextFlags_Password);

    if (ImGui::Button("PLAY!"))
    {
        nickname = std::string(buf1);
        server_address = std::string(buf2);
        password = std::string(buf3);
        generateID();
        sendJoinRequest();
    }

    if (ImGui::Button("QUIT"))
    {
        window.close();
    }

    ImGui::End();
}

void Game::draw()
{
    //window.draw(main_player.sprite);
    window.draw(crosshair);
}

void Game::generateID()
{
    ID = 0;

    for (int i = 0; i < 8; i++)
    {
        ID += std::rand() % 10;
        ID *= 10;
    }
}

void Game::send()
{
    assert(packet.getDataSize() <= sf::UdpSocket::MaxDatagramSize);
    if (UDPsocket.send(packet, server_address, server_port) != sf::Socket::Done) {}
    packet.clear();
}

void Game::sendJoinRequest()
{
    packet << static_cast<sf::Uint8>(NetCodes::JoinRequest) << nickname << ID << password;
    send();
}

void Game::sendPlayerInput()
{
    auto [x, y] = mainPlayerInputMovement();
    auto [R, L] = mainPlayerInputMouse();
    double rotation = mainPlayerInputRotation();

    packet << static_cast<sf::Uint8>(NetCodes::PlayerInput) << nickname << ID << x << y << R << L << rotation << slot << crosshair_distance;
    send();
}

void Game::listen()
{
    // unused placeholders
    sf::IpAddress remote_address;
    unsigned short remote_port;

    if (UDPsocket.receive(packet, remote_address, remote_port) != sf::Socket::Done)
        return;

    if (remote_address != server_address)
        return;

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
    //
}

void Game::receivePlayersList()
{
    sf::Int8 x, y;
    double rotation;

    if (packet >> x >> y >> rotation)
    {
        //main_player.setPosition(x, y);
        //main_player.setRotation(rotation);
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
    return std::atan2(mouse_position.y - surv::VIEW_DIM_Y / 2.0, mouse_position.x - surv::VIEW_DIM_X / 2.0) * (180.0 / surv::PI) + 90.0;
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

void Game::cleanup()
{
    static bool isCleaned = false;

    if (isCleaned) // to make sure cleanup happens only once
        return;

    free(tarFile);
    ImGui::SFML::Shutdown();
    isCleaned = true;
}
