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
            receiveJoinRequest();
            break;

        case NetCodes::PlayerInput:
            receivePlayerInput();
            break;

        default:
            break;
    }

    packet.clear();
}

void Game::receiveJoinRequest()
{
    std::string nickname;
    packet >> nickname;

    if (players.find(nickname) != players.end())
    {
        sendJoinError(ErrorCodes::NicknameExists);
        return;
    }

    if (players.size() >= surv::MAX_PLAYERS)
    {
        sendJoinError(ErrorCodes::MapFull);
        return;
    }

    players.insert(std::make_pair(nickname, std::move(player_pool.back())));
    player_pool.pop_back();
    packet >> players.at(nickname).ID
}

void Game::receivePlayerInput()
{
    //
}

void Game::broadcast()
{
    void sendPlayersList();
    void sendProjectilesList();
    void sendObjectsList();
    void sendGameState();
}

void Game::send()
{
    assert(packet.getDataSize() <= sf::UdpSocket::MaxDatagramSize);
    //if (UDPsocket.send(packet, client_address, client_port) != sf::Socket::Done) {}
    packet.clear();
}

void Game::sendJoinError(ErrorCodes)
{
    send();
}

void Game::sendPlayersList()
{
    send();
}

void Game::sendProjectilesList()
{
    send();
}

void Game::sendObjectsList()
{
    send();
}

void Game::sendGameState()
{
    send();
}

void Game::cleanup()
{
    static bool isCleaned = false;

    if (isCleaned) // to make sure cleanup happens only once
        return;

    isCleaned = true;
}
