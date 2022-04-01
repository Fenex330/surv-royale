#include "headers.hpp"

bool Game::quit = false;

Game::Game() : rng (dev()), dist (0, 9)
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
    std::string nickname, password;
    sf::Int32 ID;

    packet >> nickname >> ID >> password;

    if (players.find(nickname) != players.end())
    {
        sendJoinError(ErrorCodes::NicknameExists, address, port);
        return;
    }

    if (players.size() >= surv::MAX_PLAYERS) // || time elapsed > n seconds
    {
        sendJoinError(ErrorCodes::MapFull, address, port);
        return;
    }

    if (this->password != password)
    {
        sendJoinError(ErrorCodes::InvalidPassword, address, port);
        return;
    }

    if (std::find(banlist.begin(), banlist.end(), address.toString()) != banlist.end())
    {
        sendJoinError(ErrorCodes::IpBan, address, port);
        return;
    }

    players.insert(std::make_pair(nickname, Player()));
    players.at(nickname).ID = ID;
    players.at(nickname).address = address;
    players.at(nickname).port = port;
    cout << "player " << nickname << " joined the game" << endl;
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

    if (R) players.at(nickname).interact();
    if (L) players.at(nickname).fire();
    players.at(nickname).x += std::clamp(int(x), -1, 1) * surv::DEFAULT_PLAYER_SPEED;
    players.at(nickname).y += std::clamp(int(y), -1, 1) * surv::DEFAULT_PLAYER_SPEED;
    players.at(nickname).rotation = std::clamp(rotation, 0.0, 360.0);
    players.at(nickname).slot = std::clamp(slot, sf::Int8(1), sf::Int8(6));
    players.at(nickname).crosshair_distance = std::clamp(crosshair_distance, 0.0f, surv::CROSS_CLAMP);
}

void Game::broadcast()
{
    //std::this_thread::sleep_for(std::chrono::milliseconds(surv::SEND_DELAY));

    sf::Time elapsed = udpClock.getElapsedTime();

    if (elapsed < sf::milliseconds(surv::SEND_DELAY))
        return;

    udpClock.restart();
    assert(packet.getDataSize() <= sf::UdpSocket::MaxDatagramSize);

    for (const auto& n : players)
        if (UDPsocket.send(packet, n.second.address, n.second.port) != sf::Socket::Done) {}

    packet.clear();
}

void Game::send()
{
    sendPlayersList();
    //sendProjectilesList();
    //sendObjectsList();
    //sendGameState();
}

void Game::sendJoinError(ErrorCodes code, sf::IpAddress address, unsigned short port)
{
    packet.clear();
    packet << static_cast<sf::Uint8>(NetCodes::JoinError) << static_cast<sf::Uint8>(code);
    assert(packet.getDataSize() <= sf::UdpSocket::MaxDatagramSize);
    if (UDPsocket.send(packet, address, port) != sf::Socket::Done) {}
}

void Game::sendPlayersList()
{
    packet << static_cast<sf::Uint8>(NetCodes::PlayersList);

    for (const auto& n : players)
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
