#pragma once

#include "headers.hpp"

class Player
{
    private:
        sf::Texture texture;

    public:
        bool active;
        std::string nickname;
        sf::Sprite sprite;
        sf::View view;
        sf::Text nick;

        void init(std::string nickname); // used instead of constructor to solve missing texture bug
        void setPosition(int x, int y);
        void setRotation(double rotation);
};
