#include "headers.hpp"

void Player::init(std::string nickname)
{
    Game::loadAsset(texture, "GameData/graphics/outfits/Outfit_03.png");

    texture.setSmooth(true);
    texture.setRepeated(false);
    sprite.setTexture(texture);

    sprite.setOrigin(sprite.getLocalBounds().width * 0.5, sprite.getLocalBounds().height * 0.5);
    sprite.setPosition(surv::MAP_DIMENSION / 2, surv::MAP_DIMENSION / 2);
    sprite.setScale(0.25, 0.25);

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
    sprite.setPosition(x, y);

    if (nickname == Game::nickname)
        view.setCenter(x, y);
}

void Player::setRotation(double rotation)
{
    sprite.setRotation(rotation);
}
