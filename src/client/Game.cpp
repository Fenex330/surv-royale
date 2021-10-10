#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "../dxTarRead.h"
#include "../Global.hpp"
#include "Game.hpp"

long Game::tar_size;
unsigned char *Game::tarFile;

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

void Game::loadTexture(sf::Texture &texture, const char *path)
{   
    long file_size;

    if (!texture.loadFromMemory((void*)dxTarRead(tarFile, tar_size, path, &file_size), tar_size))
    {
        LOG("unable to load game resourses");
        exit(1);
    }
}
