#pragma once

#include "headers.hpp"

class Player
{
    public:
        bool active;
        std::string ID;
        sf::IpAddress address;
        unsigned short port;
        unsigned short slot;
        double rotation;
        float crosshair_distance;
        sf::Int16 x;
        sf::Int16 y;
        int speed;
        const int map_size;

        Player(int m_size);

        void interact();
        void fire();
        void move(sf::Int16 x_, sf::Int16 y_);
};
