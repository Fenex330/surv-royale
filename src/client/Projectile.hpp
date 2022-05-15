#pragma once

#include "headers.hpp"

class Projectile
{
    public:
        sf::RectangleShape sprite;
        Projectile(sf::Int16 x, sf::Int16 y, double rotation);
};
