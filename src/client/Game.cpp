#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "../dxTarRead.h"
#include "../config.hpp"
#include "Game.hpp"

long Game::tar_size = 0;
unsigned char *Game::tarFile = nullptr;

Game::Game() : window (sf::VideoMode (surv::VIEW_DIM_X, surv::VIEW_DIM_Y), "Main Menu")
{
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    FILE *f = fopen(GAMEDATA_PATH, "rb");

    fseek(f, 0, SEEK_END);
    tar_size = ftell(f);
    fseek(f, 0, SEEK_SET);

    tarFile = (unsigned char *)malloc(tar_size + 1);
    fread(tarFile, 1, tar_size, f);
    fclose(f);

    main_player.init();
}

Game::~Game()
{
    free(tarFile);
}

void Game::run()
{
    while (window.isOpen())  // main game loop
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

long Game::loadTexture(sf::Texture &texture, const char *path)
{   
    long file_size = 0;

    if (!texture.loadFromMemory(dxTarRead(tarFile, tar_size, path, &file_size), tar_size))
    {
        LOG("Failed to load game resources");
        exit(1);
    }

    return file_size;
}
