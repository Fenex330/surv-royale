#include <cassert>
#include "../config.hpp"
#include "Game.hpp"

bool Game::quit = false;

Game::Game()
{
    UDPsocket.setBlocking(false);
    TCPsocket.setBlocking(false);

    if (UDPsocket.bind(surv::DEFAULT_PORT) != sf::Socket::Done)
        exit(1);
}

void Game::run()
{
    while (!quit)
    {
        sf::Packet packet;

        send();
        receive();
    }
}

void Game::send()
{
    assert(packet.getDataSize() <= sf::UdpSocket::MaxDatagramSize);
    packet.clear();
}

void Game::receive()
{
}
