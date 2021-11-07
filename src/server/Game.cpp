#include "headers.hpp"

bool Game::quit = false;

Game::Game()
{
    std::atexit(Game::cleanup);

    UDPsocket.setBlocking(false);
    TCPsocket.setBlocking(false);

    if (UDPsocket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
        std::exit(1);

    //local_port = UDPsocket.getLocalPort();
}

Game::~Game()
{
    Game::cleanup();
}

void Game::run()
{
    while (!quit)
    {
        send();
        receive();
    }
}

void Game::send()
{
    sendPlayersList();
}

void Game::receive()
{
    if (UDPsocket.receive(packet, address, port) != sf::Socket::Done)
        return;

    sf::Uint8 netcode_raw;
    packet >> netcode_raw;
    NetCodes netcode = static_cast<NetCodes>(netcode_raw);

    switch (netcode)
    {
        case NetCodes::MoveAndRotate:
            if (packet >> x >> y >> rotation) {}
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

void Game::sendPlayersList()
{
    packet << static_cast<sf::Uint8>(NetCodes::PlayersList) << x << y << rotation;
    assert(packet.getDataSize() <= sf::UdpSocket::MaxDatagramSize);
    UDPsocket.send(packet, address, port);
}

void Game::receiveMoveAndRotate()
{
    //
}

void Game::cleanup()
{
    static bool isCleaned = false;

    if (isCleaned) // to make sure cleanup happens only once
        return;

    // ...
    isCleaned = true;
}
