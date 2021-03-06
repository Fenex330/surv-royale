#include "headers.hpp"

Player::Player(int map_size,
               int speed,
               std::string ID,
               sf::IpAddress address,
               unsigned short port,
               std::string nickname) : Obstacle (map_size, surv::PLAYER_RADIUS, 100),
                                       active (true),
                                       slot (1),
                                       crosshair_distance (0.0),
                                       speed (speed),
                                       ID (ID),
                                       address (address),
                                       port (port),
                                       nickname (nickname)
{
    //
}

void Player::interact()
{
    //
}

void Player::fire()
{
    items.at(slot - 1)->act(this);
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
