#pragma once

#include "headers.hpp"

class Game
{
public:

    sf::RenderWindow window;
    sf::Texture crosshair_texture;
    sf::Sprite crosshair;
    sf::UdpSocket UDPsocket;
    sf::TcpSocket TCPsocket;
    sf::Clock deltaClock;

    MainPlayer main_player;
    std::map<std::string, Player> players;
    
    static bool quit;
    static long tar_size;
    static char *tarFile;

    Game();
    ~Game();

    void run();
    void imguiMapUI();
    void draw();
    void sendMoveAndRotate(sf::Packet packet);
    void receive(sf::Packet packet);
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
