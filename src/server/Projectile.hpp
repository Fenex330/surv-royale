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
        std::function<void(Projectile*)> action;

        void move();
        void init(const std::string &nickname,
                  const sf::Int16 &x,
                  const sf::Int16 &y,
                  const double &rotation,
                  const double &damage,
                  const double &range,
                  const double &speed,
                  const double &falloff,
                  const double &headshot_multiplier,
                  const double &obstacle_multiplier,
                  const bool &potato_swap,
                  const std::function<void(Projectile*)> &action)
        {
            active = true;
            this->nickname = nickname;
            this->x = x;
            this->y = y;
            this->rotation = rotation;
            this->damage = damage;
            this->range = range;
            this->speed = speed;
            this->falloff = falloff;
            this->headshot_multiplier = headshot_multiplier;
            this->obstacle_multiplier = obstacle_multiplier;
            this->potato_swap = potato_swap;
            this->action = action;
        }
};
