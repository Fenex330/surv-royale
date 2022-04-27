#include "headers.hpp"

Bullet::Bullet(std::string nickname,
               sf::Int16 x,
               sf::Int16 y,
               double rotation,
               int damage,
               int range,
               int speed,
               double falloff,
               double headshot_multiplier;
               double obstacle_multiplier;
               double tracer_width;
               double tracer_length;
               bool is_suppressed;
               bool potato_swap;
               std::function<void(Bullet*)> action) : active (true),
                                                      count (0),
                                                      nickname (nickname),
                                                      x (x),
                                                      y (y),
                                                      rotation (rotation),
                                                      damage (damage),
                                                      range (range),
                                                      speed (speed),
                                                      falloff (falloff),
                                                      headshot_multiplier (headshot_multiplier),
                                                      obstacle_multiplier (obstacle_multiplier),
                                                      tracer_width (tracer_width),
                                                      tracer_length (tracer_length),
                                                      is_suppressed (is_suppressed),
                                                      potato_swap (potato_swap),
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
