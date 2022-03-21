#pragma once

#include "headers.hpp"

class MainPlayer : public Player
{
    public:
        sf::View view;

        MainPlayer();
        virtual ~MainPlayer() {}

        virtual void setPosition(int x, int y) override;
        virtual std::pair<sf::Int8, sf::Int8> move() override;
        virtual double rotate(const sf::RenderWindow &window) override;
};
