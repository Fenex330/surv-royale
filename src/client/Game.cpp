#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "../config.hpp"
#include "Game.hpp"

bool Game::quit = false;
long Game::tar_size = 0;
char *Game::tarFile = nullptr;

Game::Game() : window (sf::VideoMode (surv::VIEW_DIM_X, surv::VIEW_DIM_Y), "Main Menu")
{
    std::atexit(Game::cleanup);

    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    FILE *f = fopen(GAMEDATA_PATH, "rb");

    fseek(f, 0, SEEK_END);
    tar_size = ftell(f);
    fseek(f, 0, SEEK_SET);

    tarFile = (char*)malloc(tar_size + 1);
    fread(tarFile, 1, tar_size, f);
    fclose(f);

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
        window.draw(main_player.sprite);
        window.display();

        main_player.move();
        main_player.rotate(window);
    }
}

void Game::cleanup()
{
    free(tarFile);
}
