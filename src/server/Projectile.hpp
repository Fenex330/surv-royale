#pragma once

#include "headers.hpp"

class Projectile
{
    public:
        bool active;
        bool potato_swap;
        sf::Int16 x;
        sf::Int16 y;
        double damage;
        double range;
        double speed;
        double rotation;
        double falloff;
        double headshot_multiplier;
        double obstacle_multiplier;
        std::string nickname;
        std::string gunname;
        std::function<void(Projectile*)> action;

        void move();
        void init(std::string nickname, std::string gunname, sf::Int16 x, sf::Int16 y, double rotation, double damage, double range, double speed, double falloff,
                  double headshot_multiplier, double obstacle_multiplier, bool potato_swap, std::function<void(Projectile*)> action);
};
