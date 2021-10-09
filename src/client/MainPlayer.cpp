#include <cmath>
#include <SFML/Graphics.hpp>
#include "../Global.hpp"
#include "MainPlayer.hpp"

void MainPlayer::init()
{
    texture.setSmooth(true);
    texture.setRepeated(false);
    sprite.setTexture(texture);

    sprite.setOrigin(sprite.getLocalBounds().width * 0.5, sprite.getLocalBounds().height * 0.5 + 12.0);
    sprite.setPosition(surv::VIEW_DIM_X * 0.5, surv::VIEW_DIM_Y * 0.5);
    sprite.setScale(0.4, 0.4);
}

void MainPlayer::move()
{
    int mul = surv::DEFAULT_PLAYER_SPEED; // multiply by speed coefficients

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        sprite.move(1 * mul, 0);
        view.move(1 * mul, 0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        sprite.move(-1 * mul, 0);
        view.move(-1 * mul, 0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        sprite.move(0, -1 * mul);
        view.move(0, -1 * mul);
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        sprite.move(0, 1 * mul);
        view.move(0, 1 * mul);
    }
}

void MainPlayer::rotate(sf::RenderWindow &window)
{
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
    double rot = std::atan2(mouse_position.y - surv::VIEW_DIM_Y / 2, mouse_position.x - surv::VIEW_DIM_X / 2) * (180 / surv::PI) + 90;
    sprite.setRotation(rot);
}
