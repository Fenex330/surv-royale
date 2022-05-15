#include "headers.hpp"

Projectile::Projectile(sf::Int16 x, sf::Int16 y, double rotation) : x (x), y (y), rotation (rotation)
{
    sprite.setFillColor(sf::Color::White);
    sprite.setSize(sf::Vector2f(surv::PLAYER_RADIUS, 5));
}
