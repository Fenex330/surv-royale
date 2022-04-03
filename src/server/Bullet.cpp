#include "headers.hpp"

void Bullet::move()
{
    x += speed * std::cos(rotation);
    y += speed * std::sin(rotation);
}
