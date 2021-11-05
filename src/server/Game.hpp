#pragma once

#include <string>
#include <map>
#include <SFML/Network.hpp>

class Game
{
public:
    
    sf::UdpSocket UDPsocket;
    sf::TcpSocket TCPsocket;
    //std::map<std::string, Player> players;

    static bool quit;

    Game();
    void run();
};
