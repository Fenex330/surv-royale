#pragma once

#include "headers.hpp"

class Weapon : public Item
{
    public:
        std::string name;
        short rarity;
        short firing_mode;
        short ammo_type;
        sf::Int16 magazine_capacity;
        int reload_time;
        int burst_count;
        int firing_rate;
        int still_spread;
        int move_spread;
        int switch_delay;
        int player_damage;
        int obstacle_damage;
        int unit_range;
        int bullet_speed;
        double slowdown_ratio;

        Weapon(std::string name, short rarity, short firing_mode, short ammo_type, sf::Int16 magazine_capacity, int reload_time, int burst_count, int firing_rate, int still_spread,
               int move_spread, int switch_delay, int player_damage, int obstacle_damage, int unit_range, int bullet_speed, double slowdown_ratio);

        inline static void basic(Bullet* bullet) {}
};
