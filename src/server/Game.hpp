#pragma once

#include <string>
#include <map>
#include <SFML/Network.hpp>

class Game
{
public:
    
    sf::UdpSocket UDPsocket;
    sf::TcpSocket TCPsocket;

    static std::map<std::string, Player> players;

    Game();
    void run();
};
