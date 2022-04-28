#include "headers.hpp"

void Projectile::init(std::string nickname,
                 std::string gunname,
                 sf::Int16 x,
                 sf::Int16 y,
                 double rotation,
                 double damage,
                 double range,
                 double speed,
                 double falloff,
                 double headshot_multiplier,
                 double obstacle_multiplier,
                 bool potato_swap,
                 std::function<void(Projectile*)> action)
{
    active = true;
    this->nickname = nickname;
    this->gunname = gunname;
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

void Projectile::move()
{
    // damage = damage * (falloff ^ (distance/100))
    x += speed * std::cos(rotation);
    y += speed * std::sin(rotation);
    action(this);
}
