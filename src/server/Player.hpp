#pragma once

#include "headers.hpp"

class Player
{
    public:
        bool active;
        sf::IpAddress address;
        unsigned short port;
        unsigned short slot;
        double rotation;
        int x;
        int y;

        Player();
};
