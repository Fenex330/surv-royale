#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "../config.hpp"
#include "Game.hpp"

bool Game::quit = false;
long Game::tar_size = 0;
char *Game::tarFile = nullptr;

Game::Game() : window (sf::VideoMode (surv::VIEW_DIM_X, surv::VIEW_DIM_Y), "Main Menu", sf::Style::Close)
{
    std::atexit(Game::cleanup);

    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    window.setMouseCursorVisible(false);

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

    main_player.init();
}

void Game::run()
{
    while (window.isOpen() && !quit)  // main game loop
    {
        sf::Event event;
        
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
            main_player.move();
            main_player.rotate(window);

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
