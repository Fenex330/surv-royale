#include "headers.hpp"

bool Projectile::move()
{
    x += speed * std::cos(rotation);
    y += speed * std::sin(rotation);
    count += speed;
    action(this);
    return count / double(surv::PLAYER_RADIUS) > range;
}

bool Projectile::operator + (Obstacle &obj) const
{
    if (surv::getDistance(x, obj.x, y, obj.y) < obj.radius)
    {
        int headshot = surv::getRandom(0, 100) > int(surv::HEADSHOT_CHANCE * 100) ? 1 : headshot_multiplier;
        obj.hp -= damage * std::pow(falloff, count / 100) * headshot;
        return true;
    }

    return false;
}
