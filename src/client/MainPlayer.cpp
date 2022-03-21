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

std::tuple<bool, bool, bool, bool> MainPlayer::move()
{
    bool w = sf::Keyboard::isKeyPressed(sf::Keyboard::W)
    bool a = sf::Keyboard::isKeyPressed(sf::Keyboard::A)
    bool s = sf::Keyboard::isKeyPressed(sf::Keyboard::S)
    bool d = sf::Keyboard::isKeyPressed(sf::Keyboard::D)

    return std::make_tuple(w,a,s,d);
}

double MainPlayer::rotate(const sf::RenderWindow &window)
{
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
    return std::atan2(mouse_position.y - surv::VIEW_DIM_Y / 2.0, mouse_position.x - surv::VIEW_DIM_X / 2.0) * (180.0 / surv::PI) + 90.0;
}
