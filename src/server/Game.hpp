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

    std::list<Projectile> onProjectiles;
    std::list<Projectile> offProjectiles;

    std::unordered_map<std::string, Player> players;
    std::string password;
    std::mutex m;

    bool isGameRunning;
    const int id;

    static const std::array<Weapon, 1> weapons;

    Game(int id);
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
