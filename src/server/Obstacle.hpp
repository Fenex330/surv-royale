#pragma once

#include "headers.hpp"

class Obstacle
{
    public:
        double rotation;
        int radius;
        sf::Int16 hp;
        sf::Int16 x;
        sf::Int16 y;
        const int map_size;

        Obstacle(int map_size, int radius, sf::Int16 hp);
        Obstacle() : map_size (0), radius (0), hp (0) {}
};
