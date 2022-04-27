#pragma once

#include "headers.hpp"

class Game
{
public:

    sf::UdpSocket UDPsocket;
    sf::TcpSocket TCPsocket;
    sf::Packet packet;

    sf::Clock udpClock;
    sf::Clock sessionClock;

    std::unordered_map<std::string, Player> players;
    std::unordered_map<std::string, std::string> config;

    std::vector<std::string> banlist;
    std::vector<Bullet> onBullets;
    std::vector<Bullet> offBullets;

    std::string password;
    std::string command1;
    std::string command2;

    std::thread user_input;
    std::mutex m;

    std::fstream config_f;
    std::fstream banlist_f;

    std::random_device dev;
    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type> dist;

    // any static variable in this class should be declared either atomic or const
    static std::atomic<bool> quit;
    static const std::array<Weapon, 112> weapons;

    Game();
    ~Game();

    void run();
    void scan();
    void parse();

    void listen();
    void receiveJoinRequest(sf::IpAddress address, unsigned short port);
    void receivePlayerInput();

    void broadcast();
    void send();
    void sendJoinError(ErrorCodes code, sf::IpAddress address, unsigned short port);
    void sendPlayersList();
    void sendProjectilesList();
    void sendObjectsList();
    void sendGameState();
};
