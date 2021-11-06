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

    // REMOVE
    sf::Int8 x;
    sf::Int8 y;
    double rotation;
    sf::IpAddress address;
    unsigned short port;

    static bool quit;

    Game();
    void run();
    void sendPlayersList(sf::Packet packet);
    void receive(sf::Packet packet);
};
