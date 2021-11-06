#include "headers.hpp"

bool Game::quit = false;

Game::Game()
{
    UDPsocket.setBlocking(false);
    TCPsocket.setBlocking(false);

    // REMOVE
    x = 0;
    y = 0;
    rotation = 0.0;
    address = "192.168.0.11";
    port = surv::DEFAULT_PORT;

    if (UDPsocket.bind(surv::DEFAULT_PORT) != sf::Socket::Done)
    {
        std::cout << "could not bind socket\n";
        exit(1);
    }
}

void Game::run()
{
    while (!quit)
    {
        sf::Packet packet;

        sendPlayersList(packet);
        receive(packet);
    }
}

void Game::sendPlayersList(sf::Packet packet)
{
    packet << static_cast<sf::Uint8>(NetCodes::PlayersList) << x << y << rotation;
    assert(packet.getDataSize() <= sf::UdpSocket::MaxDatagramSize);
    UDPsocket.send(packet, address, port);
}

void Game::receive(sf::Packet packet)
{
    if (UDPsocket.receive(packet, address, port) != sf::Socket::Done)
        return;

    sf::Uint8 netcode_raw;
    packet >> netcode_raw;
    NetCodes netcode = static_cast<NetCodes>(netcode_raw);

    switch (netcode)
    {
        case NetCodes::MoveAndRotate:
            if (packet /*>> netcode_raw*/ >> x >> y >> rotation) {}
            else
            {
                std::cout << "could not read packet\n";
                exit(1);
            }

            break;

        default:
            break;
    }
}
