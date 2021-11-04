#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"

class MainPlayer : public Player
{
    public:
        sf::View view;

        virtual void init() override;
        virtual void setPosition(int x, int y) override;
        
        void move();
        void rotate(const sf::RenderWindow &window);

        ~MainPlayer() {};
};
