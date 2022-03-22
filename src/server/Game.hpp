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
    void receive();
    void receiveJoinRequest();
    void receivePlayerInput();

    void broadcast();
    void sendPacket();
    void sendJoinError();
    void sendPlayersList();
    void sendProjectilesList();
    void sendObjectsList();
    void sendGameState();

    static void cleanup();
};
