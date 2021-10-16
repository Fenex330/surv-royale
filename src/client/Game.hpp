#pragma once

#include <cassert>
#include <SFML/Graphics.hpp>
#include "../dxTarRead.h"
#include "../config.hpp"
#include "MainPlayer.hpp"

struct Game
{
    sf::RenderWindow window;
    MainPlayer main_player;
    static long tar_size;
    static unsigned char *tarFile;

    Game();
    ~Game();
    void run();

    template <class T> inline static
    void loadAsset(T &asset, const char *path)
    {   
        long file_size = 0;
        const char *asset_file = dxTarRead(tarFile, tar_size, path, &file_size);
        assert(file_size % 512);

        if (!asset.loadFromMemory(asset_file, tar_size))
        {
            LOG("Failed to load game resources");
            exit(1);
        }
    }
};
