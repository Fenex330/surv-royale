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
    std::vector<Projectile> onProjectiles;
    std::vector<Projectile> offProjectiles;

    std::string password;
    std::string command1;
    std::string command2;

    std::thread user_input;
    std::mutex m;

    std::fstream config_f;
    std::fstream banlist_f;

    static std::atomic<bool> quit;
    static const std::array<Weapon, 100> weapons;

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
