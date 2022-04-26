#pragma once

#include "headers.hpp"

class Bullet
{
    public:
        bool active;
        sf::Int16 x;
        sf::Int16 y;
        int count;
        int damage;
        const std::string nickname;
        const double rotation;
        const int speed;
        const std::function<void(Bullet*)> action;

        Bullet(std::string nickname, sf::Int16 x, sf::Int16 y, double rotation, int damage, int speed, std::function<void(Bullet*)> action);
        void move();
};
