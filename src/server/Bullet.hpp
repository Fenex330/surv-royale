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
        int range;
        int speed;
        double rotation;
        double falloff;
        double headshot_multiplier;
        double obstacle_multiplier;
        const double tracer_width;
        const double tracer_length;
        const bool is_suppressed;
        const bool potato_swap;
        const std::string nickname;
        const std::function<void(Bullet*)> action;

        Bullet(std::string nickname, sf::Int16 x, sf::Int16 y, double rotation, int damage, int range, int speed, double falloff, double headshot_multiplier,
               double obstacle_multiplier, double tracer_width, double tracer_length, bool is_suppressed, bool potato_swap, std::function<void(Bullet*)> action);

        void move();
};
