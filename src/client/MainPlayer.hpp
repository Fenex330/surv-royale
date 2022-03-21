#pragma once

#include "headers.hpp"

class MainPlayer : public Player
{
    public:
        sf::View view;

        MainPlayer();
        virtual ~MainPlayer() {}

        virtual void setPosition(int x, int y) override;
};
