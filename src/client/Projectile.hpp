#pragma once

#include "headers.hpp"

class Projectile
{
    public:
        sf::RectangleShape sprite;
        sf::Int16 x;
        sf::Int16 y;
        double rotation;

        Projectile(sf::Int16 x, sf::Int16 y, double rotation);
};
