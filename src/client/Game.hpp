#pragma once

#include <cassert>
#include <SFML/Graphics.hpp>
#include "dxTarRead.h"
#include "../config.hpp"
#include "MainPlayer.hpp"

class Game
{
public:

    sf::RenderWindow window;
    MainPlayer main_player;
    sf::Texture crosshair_texture;
    sf::Sprite crosshair;
    
    static bool quit;
    static long tar_size;
    static char *tarFile;

    Game();
    void run();
    void draw();
    static void cleanup();

    template <class T> inline static
    void loadAsset(T &asset, const char *path)
    {   
        long file_size = 0;
        const char *asset_file = dxTarRead(tarFile, tar_size, path, &file_size);

        assert(file_size > 0);
        assert(file_size % 512 > 0);

        if (!asset.loadFromMemory(asset_file, tar_size))
        {
            //LOG("Failed to load game resources");
            std::exit(1);
        }
    }
};
