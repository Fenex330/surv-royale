#pragma once

#include "headers.hpp"

class Weapon : public Item
{
    public:
        enum class Rarity {Common, Uncommon, Rare, Epic, Legendary, Mythic};
        enum class FiringMode {Manual, Auto, Burst, Shotgun};
        enum class AmmoType {Yellow, Red, Blue, Green};

        const std::string name;
        const Rarity rarity;
        const FiringMode firing_mode;
        const AmmoType ammo_type;
        const sf::Int16 magazine_capacity;
        const int burst_count;
        const double unit_range;
        const double stand_spread;
        const double move_spread;
        const double player_damage;
        const double projectile_speed;
        const double firing_rate;
        const double recoil_delay;
        const double switch_delay;
        const double reload_time;
        const double projectile_falloff;
        const double headshot_multiplier;
        const double obstacle_multiplier;
        const double passive_slowdown;
        const double shooting_slowdown;
        const bool potato_swap;
        const bool is_throwable;
        const std::function<void(Projectile*)> action;

        Weapon(std::string name,
               Rarity rarity,
               FiringMode firing_mode,
               AmmoType ammo_type,
               sf::Int16 magazine_capacity,
               int burst_count,
               double unit_range,
               double stand_spread,
               double move_spread,
               double player_damage,
               double projectile_speed,
               double firing_rate,
               double recoil_delay,
               double switch_delay,
               double reload_time,
               double projectile_falloff,
               double headshot_multiplier,
               double obstacle_multiplier,
               double passive_slowdown,
               double shooting_slowdown,
               bool potato_swap = true,
               bool is_throwable = false,
               const std::function<void(Projectile*)> action = [](Projectile*){}) : name (name),
                                                                                    rarity (rarity),
                                                                                    firing_mode (firing_mode),
                                                                                    ammo_type (ammo_type),
                                                                                    magazine_capacity (magazine_capacity),
                                                                                    burst_count (burst_count),
                                                                                    unit_range (unit_range),
                                                                                    stand_spread (stand_spread),
                                                                                    move_spread (move_spread),
                                                                                    player_damage (player_damage),
                                                                                    projectile_speed (projectile_speed),
                                                                                    firing_rate (firing_rate),
                                                                                    recoil_delay (recoil_delay),
                                                                                    switch_delay (switch_delay),
                                                                                    reload_time (reload_time),
                                                                                    projectile_falloff (projectile_falloff),
                                                                                    headshot_multiplier (headshot_multiplier),
                                                                                    obstacle_multiplier (obstacle_multiplier),
                                                                                    passive_slowdown (passive_slowdown),
                                                                                    shooting_slowdown (shooting_slowdown),
                                                                                    potato_swap (potato_swap),
                                                                                    is_throwable (is_throwable),
                                                                                    action (action)
                                                                                    {}
};
