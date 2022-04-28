#include "headers.hpp"

Projectile::Projectile(std::string nickname,
               std::string gunname,
               sf::Int16 x,
               sf::Int16 y,
               double rotation,
               int damage,
               int range,
               int speed,
               double falloff,
               double headshot_multiplier,
               double obstacle_multiplier,
               bool potato_swap,
               std::function<void(Projectile*)> action) : active (true),
                                                      count (0),
                                                      nickname (nickname),
                                                      gunname (gunname),
                                                      x (x),
                                                      y (y),
                                                      rotation (rotation),
                                                      damage (damage),
                                                      range (range),
                                                      speed (speed),
                                                      falloff (falloff),
                                                      headshot_multiplier (headshot_multiplier),
                                                      obstacle_multiplier (obstacle_multiplier),
                                                      potato_swap (potato_swap),
                                                      action (action)
{
    //
}

void Projectile::move()
{
    // damage = damage * (falloff ^ (count/1000))
    count++;
    x += speed * std::cos(rotation);
    y += speed * std::sin(rotation);
    action(this);
}
