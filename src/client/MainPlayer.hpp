#pragma once

#include <SFML/Graphics.hpp>

class MainPlayer
{
    public:
        sf::View view;
        sf::Sprite sprite;
        sf::Texture texture;

        MainPlayer();
        void move();
        void rotate(sf::RenderWindow &window);
};
