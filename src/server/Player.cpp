#include "headers.hpp"

Player::Player() : active(true),
                   slot(1),
                   crosshair_distance(0.0),
                   rotation(0.0),
                   x(0),
                   y(0)
{
    //
}

void Player::interact()
{
    //
}

void Player::fire()
{
    //
}

void Player::move(sf::Int16 x, sf::Int16 y)
{
    x += std::clamp(int(x), -1, 1) * surv::DEFAULT_PLAYER_SPEED;
    y += std::clamp(int(y), -1, 1) * surv::DEFAULT_PLAYER_SPEED;

    x = x < 0 ? 1 : x;
    y = y < 0 ? 1 : y;

    x = x > surv::MAP_DIMENSION ? surv::MAP_DIMENSION - 1 : x
    y = y > surv::MAP_DIMENSION ? surv::MAP_DIMENSION - 1 : y
}
