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
        bool operator + (Obstacle &obj) const; // check for collision

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
            this->x = x + surv::PLAYER_RADIUS * std::cos(rotation) * 2;
            this->y = y + surv::PLAYER_RADIUS * std::sin(rotation) * 2;
            this->rotation = rotation;
            this->damage = damage;
            this->range = range;
            this->speed = speed / double(1000 / surv::SEND_DELAY); // adjusting for update period, as speed is given per second
            this->falloff = falloff;
            this->headshot_multiplier = headshot_multiplier;
            this->obstacle_multiplier = obstacle_multiplier;
            this->action = action;
        }
};
