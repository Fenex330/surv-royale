#include <cmath>
#include "../config.hpp"
#include "MainPlayer.hpp"

void MainPlayer::init()
{
    Player::init();
    view.setSize(surv::VIEW_DIM_X, surv::VIEW_DIM_Y);
    view.setCenter(sprite.getPosition().x, sprite.getPosition().y);
}

void MainPlayer::setPosition(int x, int y)
{
    sprite.setPosition(x * surv::DEFAULT_PLAYER_SPEED, y * surv::DEFAULT_PLAYER_SPEED);
    view.setCenter(x * surv::DEFAULT_PLAYER_SPEED, y * surv::DEFAULT_PLAYER_SPEED);
}

std::pair<sf::Int8, sf::Int8> MainPlayer::move()
{
    sf::Int8 x = 0;
    sf::Int8 y = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        y = -1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        x = -1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        y = 1;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        x = 1;
    }

    return std::make_pair(x, y);
}

double MainPlayer::rotate(const sf::RenderWindow &window)
{
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
    return std::atan2(mouse_position.y - surv::VIEW_DIM_Y / 2, mouse_position.x - surv::VIEW_DIM_X / 2) * (180 / surv::PI) + 90;
}
