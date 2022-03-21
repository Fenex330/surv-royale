#include "headers.hpp"

void MainPlayer::MainPlayer()
{
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) y++;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) x--;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) y--;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) x++;

    return std::make_pair(x, y);
}

double MainPlayer::rotate(const sf::RenderWindow &window)
{
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
    return std::atan2(mouse_position.y - surv::VIEW_DIM_Y / 2.0, mouse_position.x - surv::VIEW_DIM_X / 2.0) * (180.0 / surv::PI) + 90.0;
}
