#pragma once

class Game
{
public:
    
    sf::UdpSocket UDPsocket;
    sf::TcpSocket TCPsocket;

    Game();
    void run();
};
