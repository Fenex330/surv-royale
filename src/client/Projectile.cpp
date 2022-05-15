#include "headers.hpp"

Projectile::Projectile(sf::Int16 x, sf::Int16 y, double rotation)
{
    sprite.setFillColor(sf::Color::White);
    sprite.setSize(sf::Vector2f(surv::PLAYER_RADIUS, 5));
    sprite.setPosition(x, y);
    sprite.setRotation(rotation);
}
