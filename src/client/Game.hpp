#pragma once

#include <SFML/Graphics.hpp>
#include "MainPlayer.hpp"

struct Game
{
    sf::RenderWindow window;
    MainPlayer main_player;

    Game();
    void run();
    void loadResources();
};
