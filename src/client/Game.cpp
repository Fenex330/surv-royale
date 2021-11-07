#include "headers.hpp"

bool Game::quit = false;
long Game::tar_size = 0;
char *Game::tarFile = nullptr;

Game::Game() : window (sf::VideoMode (surv::VIEW_DIM_X, surv::VIEW_DIM_Y), "Main Menu", sf::Style::Close)
{
    std::atexit(Game::cleanup);

    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    window.setMouseCursorVisible(false);

    ImGui::SFML::Init(window);

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

    main_player.init();

    UDPsocket.setBlocking(false);
    TCPsocket.setBlocking(false);

    if (UDPsocket.bind(surv::DEFAULT_PORT) != sf::Socket::Done)
        exit(1);
}

Game::~Game()
{
    Game::cleanup();
}

void Game::run()
{
    while (window.isOpen() && !quit)  // main game loop
    {
        sf::Event event;
        sf::Packet packet;
        
        while (window.pollEvent(event)) // event handler loop
        {
            ImGui::SFML::ProcessEvent(event);

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

        //imguiMapUI();

        window.clear();
        window.setView(main_player.view);
        draw();
        ImGui::SFML::Render(window);
        window.display();

        if (window.hasFocus())
        {            
            sendMoveAndRotate(packet);
            receive(packet);

            float crossX = sf::Mouse::getPosition(window).x - surv::VIEW_DIM_X / 2.0 + main_player.sprite.getPosition().x;
            float crossY = sf::Mouse::getPosition(window).y - surv::VIEW_DIM_Y / 2.0 + main_player.sprite.getPosition().y;
            crosshair.setPosition(crossX, crossY);
        }
    }
}

void imguiMapUI()
{
    ImGui::Begin("window name");
    // ...
    ImGui::End();
}

void Game::draw()
{
    window.draw(main_player.sprite);
    window.draw(crosshair);
}

void Game::sendMoveAndRotate(sf::Packet packet)
{
    auto [x, y] = main_player.move();
    double rotation = main_player.rotate(window);

    packet << static_cast<sf::Uint8>(NetCodes::MoveAndRotate) << x << y << rotation;
    assert(packet.getDataSize() <= sf::UdpSocket::MaxDatagramSize);

    if (UDPsocket.send(packet, TEST_IP, surv::DEFAULT_PORT) != sf::Socket::Done)
        exit(1);
}

void Game::receive(sf::Packet packet)
{
    sf::IpAddress address;
    unsigned short port;

    if (UDPsocket.receive(packet, address, port) != sf::Socket::Done)
        return;

    sf::Uint8 netcode_raw;
    packet >> netcode_raw;
    NetCodes netcode = static_cast<NetCodes>(netcode_raw);

    switch (netcode)
    {
        case NetCodes::PlayersList:
            sf::Int8 x, y;
            double rotation;

            if (packet >> x >> y >> rotation)
            {
                main_player.setPosition(x, y);
                main_player.setRotation(rotation);
            }
            else
                exit(1);

            break;

        default:
            break;
    }
}

void Game::cleanup()
{
    static bool isCleaned = false;

    if (isCleaned)
        return;

    free(tarFile);
    ImGui::SFML::Shutdown();
    isCleaned = true;
}
