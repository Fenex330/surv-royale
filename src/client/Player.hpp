#pragma once

#include <utility>
#include <SFML/Graphics.hpp>

class Player
{
    protected:
        sf::Texture texture;

    public:
        sf::Sprite sprite;

        virtual void init();
        virtual void setPosition(int x, int y);
        virtual std::pair<sf::Int8, sf::Int8> move() {return std::make_pair(0, 0);}
        virtual double rotate([[maybe_unused]] const sf::RenderWindow &window) {return 0.0;}

        void setRotation(int rotation);

        ~Player() {}
};
