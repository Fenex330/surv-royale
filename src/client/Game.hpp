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
    sf::Packet packet;
    sf::IpAddress server_address;
    sf::Int8 slot;

    double crosshair_distance;
    unsigned short server_port;
    std::string nickname;
    std::string password;
    std::map<std::string, Player> players;

    static bool isGameRunning;
    static bool quit;
    static long tar_size;
    static char *tarFile;

    Game();
    ~Game();

    void play();
    void run();
    void imguiMapUI();
    void draw();

    void sendJoinRequest();
    void sendPlayerInput();

    void receive();
    void receiveJoinError();
    void receivePlayersList();
    void receiveProjectilesList();
    void receiveObjectsList();
    void receiveGameState();

    void mainPlayerInputMovement();
    void mainPlayerInputMouse();
    void mainPlayerInputRotation();
    void mainPlayerInputSlot();

    static void cleanup();

    template <class T> static
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
