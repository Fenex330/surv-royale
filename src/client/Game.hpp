#pragma once

#include "headers.hpp"

class Game
{
public:

    sf::Font font;
    sf::Text text;
    sf::RenderWindow window;
    sf::Texture crosshair_texture;
    sf::Sprite crosshair;
    sf::UdpSocket UDPsocket;
    sf::TcpSocket TCPsocket;
    sf::Packet packet;
    sf::IpAddress server_address;
    sf::Int8 slot;
    sf::Int32 ID;

    sf::Clock imguiClock;
    sf::Clock udpClock;
    sf::Clock pingClock;
    sf::Clock fpsClock;

    int fps;
    int ping;
    float crosshair_distance;
    unsigned short server_port;
    std::string password;
    std::string join_error;
    std::unordered_map<std::string, Player> players;

    std::random_device dev;
    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type> dist;

    static std::string nickname;
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
    void generateID();

    void send();
    void sendJoinRequest();
    void sendPlayerInput();

    void listen();
    void receiveJoinError();
    void receivePlayersList();
    void receiveProjectilesList();
    void receiveObjectsList();
    void receiveGameState();

    std::pair<sf::Int8, sf::Int8> mainPlayerInputMovement();
    std::pair<bool, bool> mainPlayerInputMouse();
    double mainPlayerInputRotation();
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
