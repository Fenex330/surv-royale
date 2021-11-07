#pragma once

#include "headers.hpp"

class Game
{
public:
    
    sf::UdpSocket UDPsocket;
    sf::TcpSocket TCPsocket;

    //std::map<std::string, Player> players;

    static bool quit;

    Game();
    void run();
    void sendPlayersList(sf::Packet packet);
    void receive(sf::Packet packet);
};
