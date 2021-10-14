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

        if (!asset.loadFromMemory(dxTarRead(tarFile, tar_size, path, &file_size), tar_size))
        {
            LOG("Failed to load game resources");
            exit(1);
        }

        assert(file_size % 512);
    }
};
