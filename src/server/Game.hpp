#pragma once

#include "headers.hpp"

class Game
{
public:
    
    sf::UdpSocket UDPsocket;
    sf::TcpSocket TCPsocket;
    sf::Packet packet;

    std::map<std::string, Player> players;

    static bool quit;

    Game();
    ~Game();

    void run();
    void send();
    void receive();
    void sendPlayersList();
    void receiveMoveAndRotate();

    static void cleanup();
};
