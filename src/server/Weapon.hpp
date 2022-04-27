#pragma once

#include "headers.hpp"

class Weapon : public Item
{
    public:
        weapon_name;
        firing_mode;
        ammo_type;
        magazine_capacity;
        reload_time;
        bullet_count;
        firing_rate;
        still_spread;
        move_spread;
        switch_delay;
        player_damage;
        obstacle_damage;
        unit_range;
        bullet_speed;
        slowdown_ratio;

        Weapon(weapon_name, firing_mode, ammo_type, magazine_capacity, reload_time, bullet_count, firing_rate, still_spread, move_spread, switch_delay, player_damage, obstacle_damage, unit_range, bullet_speed, slowdown_ratio);
        inline static void basic(Bullet* bullet) {}
};
