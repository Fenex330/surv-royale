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
        window.draw(main_player.sprite);
        window.display();

        main_player.move();
        main_player.rotate(window);
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
    fclose(f);
    
    if (!main_player.texture.loadFromMemory((void*)dxTarRead(tarFile, tar_size, "GameData/graphics/custom/character.png", &file_size), tar_size))
    {
        LOG("unable to load game resourses");
        exit(1);
    }

    main_player.texture.setSmooth (true);
    main_player.texture.setRepeated (false);
    main_player.sprite.setTexture(main_player.texture);

    free(tarFile);
}
