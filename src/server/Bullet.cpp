#include "headers.hpp"

Bullet::Bullet(std::string nickname,
               sf::Int16 x,
               sf::Int16 y,
               double rotation,
               int damage,
               int speed,
               std::function<void(Bullet*)> action) : active (true),
                                                      nickname (nickname),
                                                      x (x),
                                                      y (y),
                                                      rotation (rotation),
                                                      damage (damage),
                                                      speed (speed),
                                                      action (action)
{
    //
}

void Bullet::move()
{
    count++;
    x += speed * std::cos(rotation);
    y += speed * std::sin(rotation);
    action(this);
}
