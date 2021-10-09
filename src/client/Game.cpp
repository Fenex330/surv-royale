#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "../dxTarRead.h"
#include "../Global.hpp"
#include "Game.hpp"

Game::Game() : window (sf::VideoMode (surv::VIEW_DIM_X, surv::VIEW_DIM_Y), "Main Menu")
{
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    loadResources();
}

void Game::run()
{
    while (window.isOpen())  // main game loop
    {
        sf::Event event;
        while (window.pollEvent (event)) // event handler loop
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
        window.draw(sprite);
        window.display();
    }
}

void Game::loadResources()
{
    long file_size;
    FILE *f = fopen("GameData.tar", "rb");

    fseek(f, 0, SEEK_END);
    long tar_size = ftell(f);
    fseek(f, 0, SEEK_SET);

    unsigned char *tarFile = (unsigned char *)malloc(tar_size + 1);
    fread(tarFile, 1, tar_size, f);
    
    if (!texture.loadFromMemory((void*)dxTarRead(tarFile, tar_size, "GameData/graphics/custom/character.png", &file_size), tar_size))
    {
        LOG("unable to load game resourses");
        free(tarFile);
        fclose(f);
        exit(1);
    }

    texture.setSmooth (true);
    texture.setRepeated (false);
    sprite.setTexture(texture);

    free(tarFile);
    fclose(f);
}
