#pragma once

#include "headers.hpp"

class Projectile
{
    public:
        bool active;
        sf::Int16 x;
        sf::Int16 y;
        double damage;
        double range;
        double speed;
        double rotation;
        double falloff;
        double headshot_multiplier;
        double obstacle_multiplier;
        const bool potato_swap;
        const std::string nickname;
        const std::string gunname;
        const std::function<void(Projectile*)> action;

        Projectile(std::string nickname, std::string gunname, sf::Int16 x, sf::Int16 y, double rotation, double damage, double range, double speed, double falloff,
               double headshot_multiplier, double obstacle_multiplier, bool potato_swap, std::function<void(Projectile*)> action);

        void move();
};
