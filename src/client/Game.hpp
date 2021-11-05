#pragma once

#include <cassert>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "dxTarRead.h"
#include "MainPlayer.hpp"

class Game
{
public:

    sf::RenderWindow window;
    sf::Texture crosshair_texture;
    sf::Sprite crosshair;
    sf::UdpSocket UDPsocket;
    sf::TcpSocket TCPsocket;
    MainPlayer main_player;
    std::map<std::string, Player> players;
    
    static bool quit;
    static long tar_size;
    static char *tarFile;

    Game();
    void run();
    void draw();
    void send();
    static void cleanup();

    template <class T> inline static
    void loadAsset(T &asset, const char *path)
    {   
        long file_size = 0;
        const char *asset_file = dxTarRead(tarFile, tar_size, path, &file_size);

        assert(file_size > 0);
        assert(file_size % 512 > 0);

        if (!asset.loadFromMemory(asset_file, tar_size))
            std::exit(1);
    }
};
