#pragma once

#include <SFML/Graphics.hpp>
#include "MainPlayer.hpp"

struct Game
{
    sf::RenderWindow window;
    MainPlayer main_player;
    static long tar_size = 0;
    static unsigned char *tarFile = nullptr;

    Game();
    ~Game();
    void run();
    static void loadResources(sf::Texture &texture, const char *path);
};
