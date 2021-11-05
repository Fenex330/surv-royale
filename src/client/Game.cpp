#include <cstdlib>
#include "../config.hpp"
#include "Game.hpp"

// REMOVE
#define TEST_IP "192.168.0.5"
#define TEST_NICK "test"

bool Game::quit = false;
long Game::tar_size = 0;
char *Game::tarFile = nullptr;

Game::Game() : window (sf::VideoMode (surv::VIEW_DIM_X, surv::VIEW_DIM_Y), "Main Menu", sf::Style::Close)
{
    std::atexit(Game::cleanup);

    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    window.setMouseCursorVisible(false);

    UDPsocket.setBlocking(false);
    TCPsocket.setBlocking(false);

    FILE *f = fopen(GAMEDATA_PATH, "rb");

    fseek(f, 0, SEEK_END);
    tar_size = ftell(f);
    fseek(f, 0, SEEK_SET);

    tarFile = (char*)malloc(tar_size + 1);
    fread(tarFile, 1, tar_size, f);
    fclose(f);

    Game::loadAsset(crosshair_texture, "GameData/graphics/crosshairs/11.png");
    crosshair.setTexture(crosshair_texture);
    crosshair.setScale(0.5, 0.5);

    if (UDPsocket.bind(surv::DEFAULT_PORT) != sf::Socket::Done)
        exit(1);

    main_player.init();
}

void Game::run()
{
    while (window.isOpen() && !quit)  // main game loop
    {
        sf::Event event;
        sf::Packet packet;
        
        while (window.pollEvent(event)) // event handler loop
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
        }

        window.clear();
        window.setView(main_player.view);
        draw();
        window.display();

        if (window.hasFocus())
        {
            auto [x, y] = main_player.move();
            double rotation = main_player.rotate(window);

            packet << static_cast<sf::Uint8>(NetCodes::MoveAndRotate) << x << y << rotation;
            assert(packet.getDataSize() <= sf::UdpSocket::MaxDatagramSize);

            if (UDPsocket.send(packet, TEST_IP, surv::DEFAULT_PORT) != sf::Socket::Done)
                exit(1);

            packet.clear();
            crosshair.setPosition(sf::Mouse::getPosition(window).x - surv::VIEW_DIM_X / 2 + main_player.sprite.getPosition().x,
                                  sf::Mouse::getPosition(window).y - surv::VIEW_DIM_Y / 2 + main_player.sprite.getPosition().y);
        }
    }
}

void Game::draw()
{
    window.draw(main_player.sprite);
    window.draw(crosshair);
}

void Game::cleanup()
{
    free(tarFile);
}
