#include "headers.hpp"

Player::Player(int m_size) : active (true),
                   map_size (m_size),
                   slot (1),
                   crosshair_distance (0.0),
                   rotation (0.0)
{
    x = map_size / 2;
    y = map_size / 2;
}

void Player::interact()
{
    //
}

void Player::fire()
{
    //
}

void Player::move(sf::Int16 x_, sf::Int16 y_)
{
    x += std::clamp(int(x_), -1, 1) * speed;
    y += std::clamp(int(y_), -1, 1) * speed;

    x = x < 0 ? 1 : x;
    y = y < 0 ? 1 : y;

    x = x > map_size ? map_size - 1 : x;
    y = y > map_size ? map_size - 1 : y;
}
