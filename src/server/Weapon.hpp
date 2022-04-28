#pragma once

#include "headers.hpp"

class Weapon : public Item
{
    public:
        enum class Rarity {Common, Uncommon, Rare, Epic, Legendary, Mythic};
        enum class FiringMode {Manual, Auto, Burst, Shotgun};
        enum class AmmoType {Yellow, Red, Blue, Green};

        std::string name;
        Rarity rarity;
        FiringMode firing_mode;
        AmmoType ammo_type;
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
        int Projectile_speed;
        double Projectile_falloff;
        double headshot_multiplier;
        double obstacle_multiplier;
        double passive_slowdown;
        double shooting_slowdown;
        bool potato_swap;
        bool is_throwable;
        std::function<void(Projectile*)> action;

        Weapon(std::string name, Rarity rarity, FiringMode firing_mode, AmmoType ammo_type, sf::Int16 magazine_capacity, int reload_time, int burst_count, int firing_rate, int recoil_delay,
               int stand_spread, int move_spread, int switch_delay, int player_damage, int unit_range, int Projectile_speed, double Projectile_falloff, double headshot_multiplier,
               double obstacle_multiplier, double passive_slowdown, double shooting_slowdown, bool potato_swap = true, bool is_throwable = false, std::function<void(Projectile*)> action = [](Bullet*){});
};
