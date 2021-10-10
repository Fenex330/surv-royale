#pragma once

#include <SFML/Graphics.hpp>
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
    static void loadTexture(sf::Texture &texture, const char *path);
};
