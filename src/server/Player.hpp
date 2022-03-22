#pragma once

#include "headers.hpp"

class Player
{
    public:
        bool active;
        sf::Int32 ID;
        sf::IpAddress address;
        unsigned short port;
        unsigned short slot;
        double rotation;
        float crosshair_distance;
        int x;
        int y;

        Player();
};
