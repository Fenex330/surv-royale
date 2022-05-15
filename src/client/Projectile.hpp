#pragma once

#include "headers.hpp"

class Projectile
{
    public:
        sf::Int16 x;
        sf::Int16 y;
        double rotation;

        static sf::RectangleShape sprite;
};
