#pragma once

#include "headers.hpp"

class Projectile : public Obstacle
{
    public:
        bool potato_swap;
        std::string nickname;
        double count;
        double damage;
        double range;
        double speed;
        double falloff;
        double headshot_multiplier;
        double obstacle_multiplier;
        Delegate action;

        bool move();
        bool operator + (Obstacle &obj) const;

        void init(bool potato_swap,
                  const std::string &nickname,
                  const sf::Int16 &x,
                  const sf::Int16 &y,
                  double rotation,
                  double damage,
                  double range,
                  double speed,
                  double falloff,
                  double headshot_multiplier,
                  double obstacle_multiplier,
                  Delegate action)
        {
            count = 0.0;
            this->potato_swap = potato_swap;
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
            this->action = action;
        }
};
