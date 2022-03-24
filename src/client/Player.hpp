#pragma once

#include "headers.hpp"

class Player
{
    protected:
        sf::Texture texture;

    public:
        bool active;
        sf::Sprite sprite;
        sf::View view;

        Player();
        virtual ~Player() {}

        virtual void setPosition(int x, int y);
        void setRotation(double rotation);
};
