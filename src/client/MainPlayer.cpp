#include "headers.hpp"

MainPlayer::MainPlayer()
{
    view.setSize(surv::VIEW_DIM_X, surv::VIEW_DIM_Y);
    view.setCenter(sprite.getPosition().x, sprite.getPosition().y);
}

void MainPlayer::setPosition(int x, int y)
{
    sprite.setPosition(x * surv::DEFAULT_PLAYER_SPEED, y * surv::DEFAULT_PLAYER_SPEED);
    view.setCenter(x * surv::DEFAULT_PLAYER_SPEED, y * surv::DEFAULT_PLAYER_SPEED);
}
