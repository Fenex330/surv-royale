#include "headers.hpp"

void Player::init(std::string nickname)
{
    Game::loadAsset(texture, "GameData/graphics/custom/character.png");

    texture.setSmooth(true);
    texture.setRepeated(false);
    sprite.setTexture(texture);

    sprite.setOrigin(sprite.getLocalBounds().width * 0.5, sprite.getLocalBounds().height * 0.5 + 12.0);
    sprite.setScale(0.3, 0.3);

    active = true;
    this->nickname = nickname;

    if (nickname == Game::nickname)
    {
        view.setSize(surv::VIEW_DIM_X, surv::VIEW_DIM_Y);
        view.setCenter(sprite.getPosition().x, sprite.getPosition().y);
    }
}

void Player::setPosition(int x, int y)
{
    sprite.setPosition(x * surv::DEFAULT_PLAYER_SPEED, y * surv::DEFAULT_PLAYER_SPEED);

    if (nickname == Game::nickname)
        view.setCenter(x * surv::DEFAULT_PLAYER_SPEED, y * surv::DEFAULT_PLAYER_SPEED);
}

void Player::setRotation(double rotation)
{
    sprite.setRotation(rotation);
}
