#pragma once

#include "headers.hpp"

class Game
{
public:

    sf::UdpSocket UDPsocket;
    sf::TcpSocket TCPsocket;
    sf::Packet packet;

    std::unordered_map<std::string, Player> players;

    static bool quit;

    Game();
    ~Game();

    void run();
    void listen();
    void receiveJoinRequest(sf::IpAddress address, unsigned short port);
    void receivePlayerInput();

    void broadcast();
    void send();
    void sendJoinError(ErrorCodes code, std::string nickname);
    void sendPlayersList();
    void sendProjectilesList();
    void sendObjectsList();
    void sendGameState();

    static void cleanup();
};
