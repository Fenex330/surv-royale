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
        int speed;
        double rotation;
        double falloff;
        const std::string nickname;
        const std::function<void(Bullet*)> action;

        Bullet(std::string nickname, sf::Int16 x, sf::Int16 y, double rotation, int damage, int speed, double falloff, std::function<void(Bullet*)> action);
        void move();
};
