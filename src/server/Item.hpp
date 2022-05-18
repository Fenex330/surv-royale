#pragma once

#include "headers.hpp"

class Player;

class Item
{
    public:
        virtual void act(Player* player) = 0;
        virtual ~Item() {}
};
