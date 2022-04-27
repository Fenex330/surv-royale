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
        int recoil_delay;
        int stand_spread;
        int move_spread;
        int switch_delay;
        int player_damage;
        int unit_range;
        int bullet_speed;
        double bullet_falloff;
        double headshot_multiplier;
        double obstacle_multiplier;
        double passive_slowdown;
        double shooting_slowdown;
        bool potato_swap;

        Weapon(std::string name, short rarity, short firing_mode, short ammo_type, sf::Int16 magazine_capacity, int reload_time, int burst_count, int firing_rate, int recoil_delay, int stand_spread,
               int move_spread, int switch_delay, int player_damage, int unit_range, int bullet_speed, double bullet_falloff, double headshot_multiplier, double obstacle_multiplier, double passive_slowdown,
               double shooting_slowdown, bool potato_swap);

        inline static void basic ([[maybe_unused]] Bullet* bullet) {}
};
