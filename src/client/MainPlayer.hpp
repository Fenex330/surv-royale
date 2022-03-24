#pragma once

#include "headers.hpp"

class MainPlayer : public Player
{
    public:
        MainPlayer();
        virtual ~MainPlayer() {}

        virtual void setPosition(int x, int y) override;
};
