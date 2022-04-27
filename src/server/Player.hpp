#pragma once

#include "headers.hpp"

class Player : public Obstacle
{
    public:
        bool active;
        std::string ID;
        sf::IpAddress address;
        unsigned short port;
        unsigned short slot;
        float crosshair_distance;
        int speed;
        const int map_size;
        std::array<Item, 6> items;

        Player(int map_size, int speed, std::string ID, sf::IpAddress address, unsigned short port);

        void interact();
        void fire();
        void move(sf::Int16 x_, sf::Int16 y_);
};
