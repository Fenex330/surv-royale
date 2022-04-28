#include "headers.hpp"

void Projectile::move()
{
    // damage = damage * (falloff ^ (distance/100))
    x += speed * std::cos(rotation);
    y += speed * std::sin(rotation);
    action(this);
}
