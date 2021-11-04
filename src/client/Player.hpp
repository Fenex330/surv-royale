#pragma once

#include <SFML/Graphics.hpp>

class Player
{
    protected:
        sf::Texture texture;

    public:
        sf::Sprite sprite;

        virtual void init();
        virtual void setPosition(int x, int y);
        
        void setRotation(int rotation);

        ~Player() {};
};
