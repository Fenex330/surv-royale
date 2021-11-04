#include <SFML/Graphics.hpp>
#include "../config.hpp"
#include "Game.hpp"
#include "Player.hpp"

void Player::init()
{
    Game::loadAsset(texture, "GameData/graphics/custom/character.png");

    texture.setSmooth(true);
    texture.setRepeated(false);
    sprite.setTexture(texture);

    sprite.setOrigin(sprite.getLocalBounds().width * 0.5, sprite.getLocalBounds().height * 0.5 + 12.0);
    sprite.setScale(0.3, 0.3);
}

void Player::setPosition(int x, int y)
{
    sprite.setPosition(x * surv::DEFAULT_PLAYER_SPEED, y * surv::DEFAULT_PLAYER_SPEED);
}

void Player::setRotation(int rotation)
{
    sprite.setRotation(rotation);
}
