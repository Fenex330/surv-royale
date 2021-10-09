#pragma once

#include <SFML/Graphics.hpp>

class MainPlayer
{
    public:
        sf::View view;
        sf::Sprite sprite;
        sf::Texture texture;

        void move();
        void rotate(const sf::RenderWindow &window);
};
