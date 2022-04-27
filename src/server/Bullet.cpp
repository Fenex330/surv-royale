#include "headers.hpp"

Bullet::Bullet(std::string nickname,
               sf::Int16 x,
               sf::Int16 y,
               double rotation,
               int damage,
               int speed,
               double falloff,
               std::function<void(Bullet*)> action) : active (true),
                                                      count (0),
                                                      nickname (nickname),
                                                      x (x),
                                                      y (y),
                                                      rotation (rotation),
                                                      damage (damage),
                                                      speed (speed),
                                                      falloff (falloff),
                                                      action (action)
{
    //
}

void Bullet::move()
{
    // damage = damage * (falloff ^ (count/1000))
    count++;
    x += speed * std::cos(rotation);
    y += speed * std::sin(rotation);
    action(this);
}
