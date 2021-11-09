#pragma once

#include "headers.hpp"

class Player
{
    public:
        bool active;
        sf::IpAddress address;
        unsigned short server_port;
        int x;
        int y;
        double rotation;

        Player();
};
