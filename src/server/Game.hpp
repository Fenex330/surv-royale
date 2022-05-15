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
    const std::unordered_map<std::string, std::string> config;
          std::string password;

    bool isGameRunning;
    const int id;

    static const std::array<Weapon, 1> weapons;
    static thread_local std::list<Projectile*> onProjectiles;
    static thread_local std::list<Projectile*> offProjectiles;

    Game(int id, std::unordered_map<std::string, std::string> config);
    ~Game();

    void run();
    void parse();

    void listen();
    void receiveJoinRequest(sf::IpAddress address, unsigned short port);
    void receivePlayerInput();

    void send();
    void sendJoinError(ErrorCodes code, sf::IpAddress address, unsigned short port);
    void sendPlayersList();
    void sendProjectilesList();
    void sendObjectsList();
    void sendGameState();
};
