#include <SFML/Graphics.hpp>

class MainPlayer
{
    public:
        void move();
        void rotate(const sf::RenderWindow &window);

    private:
        sf::View view;
        sf::Sprite sprite;
};
