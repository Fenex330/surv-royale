#include <SFML/Graphics.hpp>
#include <zipper/unzipper.h>
#include "../Global.hpp"

int main()
{
    sf::RenderWindow window (sf::VideoMode (surv::VIEW_DIM_X, surv::VIEW_DIM_Y), "Main Menu");

    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    /*// Set Window Icon
    sf::Image icon;
    icon.loadFromFile ("GameData/graphics/logo/logo-surviv.png");
    window.setIcon (icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());*/

    std::vector<unsigned char> unzipped_entry;
    zipper::Unzipper unzipper ("GameData.zip");
    unzipper.extractEntryToMemory("GameData/graphics/custom/character.png", unzipped_entry);
    unzipper.close();

    unsigned char *entry = new unsigned char [unzipped_entry.size()];

    for (size_t i = 0; i < unzipped_entry.size(); i++)
    {
        entry[i] = unzipped_entry.at(i);
    }

    sf::Texture texture;
    sf::Sprite sprite;
    
    if (!texture.loadFromMemory((void*)entry, unzipped_entry.size()))
    {
        LOG("unable to load game resourses");
        delete[] entry;
        exit(1);
    }

    texture.setSmooth (true);
    texture.setRepeated (false);
    sprite.setTexture(texture);

    while (window.isOpen())  // main game loop
    {
        sf::Event event;
        while (window.pollEvent (event)) // event handler loop
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    delete[] entry;
    return EXIT_SUCCESS;
}
