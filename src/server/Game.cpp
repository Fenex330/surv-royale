#include "headers.hpp"

bool Game::quit = false;

Game::Game()
{
    std::atexit(Game::cleanup);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

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
        send();
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
        packet.clear();
        sendJoinError(ErrorCodes::NicknameExists, nickname);
        return;
    }

    if (players.size() >= surv::MAX_PLAYERS) // || time elapsed > n seconds
    {
        packet.clear();
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
    std::string nickname;
    sf::Int32 ID;

    packet >> nickname >> ID;

    if (players.find(nickname) == players.end())
        return;

    if (players.at(nickname).ID != ID)
        return;

    sf::Int8 x, y, slot;
    bool R, L;
    double rotation;
    float crosshair_distance;

    packet >> x >> y >> R >> L >> rotation >> slot >> crosshair_distance;
}

void Game::broadcast()
{
    assert(packet.getDataSize() <= sf::UdpSocket::MaxDatagramSize);

    for(const auto& n : players)
    {
        if (UDPsocket.send(packet, n.second.address, n.second.port) != sf::Socket::Done) {}
    }

    packet.clear();
}

void Game::send()
{
    void sendPlayersList();
    //void sendProjectilesList();
    //void sendObjectsList();
    //void sendGameState();
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
    packet << static_cast<sf::Uint8>(NetCodes::PlayersList);

    for(const auto& n : players)
        packet << n.first << n.second.x << n.second.y << n.second.rotation;

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
