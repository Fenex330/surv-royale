#include "headers.hpp"

bool Game::quit = false;

Game::Game()
{
    std::atexit(Game::cleanup);

    UDPsocket.setBlocking(false);
    TCPsocket.setBlocking(false);

    if (UDPsocket.bind(surv::DEFAULT_PORT) != sf::Socket::Done)
        std::exit(1);
}

Game::~Game()
{
    Game::cleanup();
}

void Game::run()
{
    while (!quit)
    {
        broadcast();
        listen();
    }
}

void Game::listen()
{
    sf::IpAddress remote_address;
    unsigned short remote_port;

    if (UDPsocket.receive(packet, remote_address, remote_port) != sf::Socket::Done)
        return;

    sf::Uint8 netcode_raw;
    packet >> netcode_raw;
    NetCodes netcode = static_cast<NetCodes>(netcode_raw);

    switch (netcode)
    {
        case NetCodes::JoinRequest:
            receiveJoinRequest(remote_address, remote_port);
            break;

        case NetCodes::PlayerInput:
            receivePlayerInput();
            break;

        default:
            break;
    }

    packet.clear();
}

void Game::receiveJoinRequest(sf::IpAddress address, unsigned short port)
{
    std::string nickname;
    packet >> nickname;

    if (players.find(nickname) != players.end())
    {
        sendJoinError(ErrorCodes::NicknameExists, nickname);
        return;
    }

    if (players.size() >= surv::MAX_PLAYERS)
    {
        sendJoinError(ErrorCodes::MapFull, nickname);
        return;
    }

    players.insert(std::make_pair(nickname, Player()));
    packet >> players.at(nickname).ID;
    players.at(nickname).address = address;
    players.at(nickname).port = port;
    std::cout << "player " << nickname << " joined the game" << std::endl;
}

void Game::receivePlayerInput()
{
    //
}

void Game::broadcast()
{
    //assert(packet.getDataSize() <= sf::UdpSocket::MaxDatagramSize);
    //if (UDPsocket.send(packet, client_address, client_port) != sf::Socket::Done) {}
    //packet.clear();
}

void Game::send()
{
    void sendPlayersList();
    void sendProjectilesList();
    void sendObjectsList();
    void sendGameState();
}

void Game::sendJoinError(ErrorCodes code, std::string nickname)
{
    packet << static_cast<sf::Uint8>(NetCodes::JoinError) << static_cast<sf::Uint8>(code);
    assert(packet.getDataSize() <= sf::UdpSocket::MaxDatagramSize);
    if (UDPsocket.send(packet, players.at(nickname).address, players.at(nickname).port) != sf::Socket::Done) {}
    packet.clear();
}

void Game::sendPlayersList()
{
    broadcast();
}

void Game::sendProjectilesList()
{
    broadcast();
}

void Game::sendObjectsList()
{
    broadcast();
}

void Game::sendGameState()
{
    broadcast();
}

void Game::cleanup()
{
    static bool isCleaned = false;

    if (isCleaned) // to make sure cleanup happens only once
        return;

    isCleaned = true;
}
