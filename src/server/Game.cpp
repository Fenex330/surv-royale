#include "headers.hpp"

const std::array<Weapon, 1> Game::weapons
{
    Weapon("AK-47", Weapon::Rarity::Common, Weapon::FiringMode::Auto, Weapon::AmmoType::Blue, 30, 1, 200.0, 2.5, 10.0, 13.5, 100.0, 0.1, 0.0, 0.75, 2.5, 0.9, 2.0, 1.0, 1.0, 1.0)
};

thread_local std::list<Projectile> Game::onProjectiles;
thread_local std::list<Projectile> Game::offProjectiles;

Game::Game(int id, std::unordered_map<std::string, std::string> config) : isGameRunning (false), id (id), config (config)
{
    password = config.at("password") == "-" ? "" : config.at("password");
    offProjectiles.resize(std::stoi(config.at("max_bullets")));

    UDPsocket.setBlocking(false);
    TCPsocket.setBlocking(false);

    if (UDPsocket.bind(std::stoi(config.at("port")) + id - 1) != sf::Socket::Done)
        Manager::quit = true;
}

Game::~Game()
{
    packet.clear();
    packet << static_cast<sf::Uint8>(NetCodes::JoinError) << static_cast<sf::Uint8>(ErrorCodes::Kick);

    for (const auto& [nickname, player] : players)
        UDPsocket.send(packet, player.address, player.port);

    std::lock_guard<std::mutex> lock (Manager::m);
    clog << "shutdown room " << id << endl;
}

void Game::run()
{
    while (!Manager::quit)
    {
        send();
        listen();
        parse();

        if (!isGameRunning)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(surv::SEND_DELAY));
            sessionClock.restart();
        }
    }
}

void Game::parse()
{
    if (Manager::id != id)
        return;

    std::lock_guard<std::mutex> lock (Manager::m);

    if (Manager::command1 == "list")
    {
        for (const auto& [nickname, player] : players)
            cout << player.ID << " " << player.address << " " << player.port << " " << nickname << endl;
    }
    else if (Manager::command1 == "kick")
    {
        std::string nick = Manager::command2;
        sendJoinError(ErrorCodes::Kick, players.at(nick).address, players.at(nick).port);
        players.erase(nick);
    }
    else if (Manager::command1 == "ban")
    {
        std::string nick = Manager::command2;
        sendJoinError(ErrorCodes::IpBan, players.at(nick).address, players.at(nick).port);
        Manager::banlist.insert(players.at(nick).address.toString());
        Manager::banlist_f.clear();
        Manager::banlist_f << players.at(nick).address.toString() << endl;
        Manager::banlist_f.flush();
        players.erase(nick);
    }
    else if (Manager::command1 == "unban")
    {
        //
    }
    else
    {
        cerr << "unknown command" << endl;
    }

    Manager::id = 0;
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
    std::string nickname, ID, password, version;
    sf::Time elapsed = sessionClock.getElapsedTime();
    std::unordered_set<std::string> banlist;

    {
        std::lock_guard<std::mutex> lock (Manager::m);
        banlist = Manager::banlist;
    }

    packet >> nickname >> ID >> password >> version;

    if (version != GAME_VERSION)
    {
        packet.clear();
        packet << static_cast<sf::Uint8>(NetCodes::JoinError) << static_cast<sf::Uint8>(ErrorCodes::InvalidVersion) << std::string(GAME_VERSION);
        UDPsocket.send(packet, address, port);
        return;
    }

    if (std::find(banlist.begin(), banlist.end(), address.toString()) != banlist.end())
    {
        sendJoinError(ErrorCodes::IpBan, address, port);
        return;
    }

    if (this->password != password)
    {
        sendJoinError(ErrorCodes::InvalidPassword, address, port);
        return;
    }

    if (players.size() >= std::stoul(config.at("max_players")) || elapsed > sf::seconds(std::stoi(config.at("join_time"))))
    {
        sendJoinError(ErrorCodes::MapFull, address, port);
        return;
    }

    if (players.find(nickname) != players.end() || nickname.find(' ') != std::string::npos || nickname.empty())
    {
        sendJoinError(ErrorCodes::NicknameExists, address, port);
        return;
    }

    players.insert(std::make_pair(nickname, Player(std::stoi(config.at("map_size")) * surv::SQUARE_SIZE * surv::PLAYER_RADIUS, std::stoi(config.at("player_speed")), ID, address, port)));
    clog << nickname << " joined room " << id << endl;
    isGameRunning = true;
}

void Game::receivePlayerInput()
{
    std::string nickname;
    std::string ID;

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
    players.at(nickname).move(x, y);
    players.at(nickname).rotation = std::clamp(rotation, 0.0, surv::PI * 2.0);
    players.at(nickname).slot = std::clamp(slot, sf::Int8(1), sf::Int8(6));
    players.at(nickname).crosshair_distance = std::clamp(crosshair_distance, 0.0f, surv::FOV);
}

void Game::send()
{
    sf::Time elapsed = udpClock.getElapsedTime();

    if (elapsed < sf::milliseconds(surv::SEND_DELAY))
        return;

    udpClock.restart();

    sendPlayersList();
    sendProjectilesList();
    sendObjectsList();
    sendGameState();
}

void Game::sendJoinError(ErrorCodes code, sf::IpAddress address, unsigned short port)
{
    packet.clear();
    packet << static_cast<sf::Uint8>(NetCodes::JoinError) << static_cast<sf::Uint8>(code);
    UDPsocket.send(packet, address, port);
}

void Game::sendPlayersList()
{
    for (const auto& [nickname, player] : players) // for each destination address
    {
        packet.clear();
        packet << static_cast<sf::Uint8>(NetCodes::PlayersList);

        for (const auto& [nickname_, player_] : players) // for each object to place in packet
        {
            if (surv::getDistance(player.x, player_.x, player.y, player_.y) < surv::FOV * 1.5f)
                packet << nickname_ << player_.x << player_.y << player_.rotation;
        }

        assert(packet.getDataSize() <= sf::UdpSocket::MaxDatagramSize);
        if (UDPsocket.send(packet, player.address, player.port) != sf::Socket::Done) {}
    }
}

void Game::sendProjectilesList()
{
    //
}

void Game::sendObjectsList()
{
    //
}

void Game::sendGameState()
{
    packet.clear();
    packet << static_cast<sf::Uint8>(NetCodes::GameState) << static_cast<sf::Uint16>(std::stoi(config.at("map_size")));

    for (const auto& [nickname, player] : players)
        UDPsocket.send(packet, player.address, player.port);
}
