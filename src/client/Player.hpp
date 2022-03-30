#pragma once

#include "headers.hpp"

class Player
{
    private:
        std::string nickname;
        sf::Texture texture;

    public:
        bool active;
        sf::Sprite sprite;
        sf::View view;

        Player(std::string nickname);

        void setPosition(int x, int y);
        void setRotation(double rotation);
};
