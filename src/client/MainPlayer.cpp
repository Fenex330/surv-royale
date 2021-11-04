#include <cmath>
#include <SFML/Graphics.hpp>
#include "../config.hpp"
#include "MainPlayer.hpp"

void MainPlayer::init()
{
    Player::init();
    view.setCenter(sprite.getPosition().x, sprite.getPosition().y);
    view.setSize(surv::VIEW_DIM_X, surv::VIEW_DIM_Y);
}

void Player::setPosition(int x, int y)
{
    sprite.setPosition(x * surv::DEFAULT_PLAYER_SPEED, y * surv::DEFAULT_PLAYER_SPEED);
    view.setCenter(x * surv::DEFAULT_PLAYER_SPEED, y * surv::DEFAULT_PLAYER_SPEED);
}

void MainPlayer::move()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        //(1, 0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        //(-1, 0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        //(0, -1);
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        //(0, 1);
    }
}

void MainPlayer::rotate(const sf::RenderWindow &window)
{
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
    double rot = std::atan2(mouse_position.y - surv::VIEW_DIM_Y / 2, mouse_position.x - surv::VIEW_DIM_X / 2) * (180 / surv::PI) + 90;
}
