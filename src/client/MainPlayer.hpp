#pragma once

#include <utility>
#include "Player.hpp"

class MainPlayer : public Player
{
    public:
        sf::View view;

        virtual void init() override;
        virtual void setPosition(int x, int y) override;
        
        std::pair<int, int> move();
        double rotate(const sf::RenderWindow &window);

        ~MainPlayer() {};
};
