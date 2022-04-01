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

        void init(std::string nickname); // is used instead if constructor to solve missing texture bug
        void setPosition(int x, int y);
        void setRotation(double rotation);
};
