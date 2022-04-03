#pragma once

#include "headers.hpp"

class Bullet
{
    public:
        std::string nickname;
        sf::Int16 x;
        sf::Int16 y;
        double rotation;
        int damage;
        int speed;

        void move();
};
