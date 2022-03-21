#pragma once

#include "headers.hpp"

class Player
{
    protected:
        sf::Texture texture;

    public:
        bool active;
        sf::Sprite sprite;

        Player();
        virtual ~Player() {}

        virtual void setPosition(int x, int y);
        void setRotation(double rotation);
};
