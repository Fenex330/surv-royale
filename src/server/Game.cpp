#include "headers.hpp"

std::atomic<bool> Game::quit (false);

Game::Game() : rng (dev()),
               dist (0, 9),
               user_input (&Game::scan, this)
{
    user_input.detach();
    clog << "SurvRoyale version " << GAME_VERSION << endl;

    #ifdef _WIN32
        config_f.open(SERVER_CONF_PATH, std::ios::in);
        banlist_f.open(BANLIST_PATH, std::ios::in | std::ios::out | std::ios::app);
    #else
        const std::string HOME = std::getenv("HOME");

        if (!fs::exists(HOME + CONFIG_DIR))
            fs::create_directory(HOME + CONFIG_DIR);

        if (!fs::exists(HOME + SERVER_CONF_PATH))
            fs::copy_file(DEFAULT_SERVER_CONF_PATH, HOME + SERVER_CONF_PATH);

        config_f.open(HOME + SERVER_CONF_PATH, std::ios::in);
        banlist_f.open(HOME + BANLIST_PATH, std::ios::in | std::ios::out | std::ios::app);
    #endif

    if (!config_f)
    {
        cerr << "server.conf open error" << endl;
        std::exit(1);
    }

    if (!banlist_f)
    {
        cerr << "banlist.txt open error" << endl;
        std::exit(1);
    }

    while (!config_f.eof())
    {
        std::string param;
        std::string value;
        config_f >> param >> value;
        config[param] = value;
    }

    while (!banlist_f.eof())
    {
        std::string line;
        std::getline(banlist_f, line);
        banlist.push_back(line);
    }

    password = config.at("password") == "-" ? "" : config.at("password");

    UDPsocket.setBlocking(false);
    TCPsocket.setBlocking(false);
    int i = 0;

    while (UDPsocket.bind(std::stoi(config.at("port")) + i) != sf::Socket::Done) i++;
    clog << "binded to port " << UDPsocket.getLocalPort() << endl;
}

Game::~Game()
{
    packet.clear();
    packet << static_cast<sf::Uint8>(NetCodes::JoinError) << static_cast<sf::Uint8>(ErrorCodes::Kick);

    for (const auto& n : players)
        UDPsocket.send(packet, n.second.address, n.second.port);
}

void Game::run()
{
    while (!quit)
    {
        send();
        listen();
        parse();
    }
}

void Game::scan()
{
    while (!quit)
    {
        std::string buffer1;
        std::string buffer2;
        cin >> buffer1 >> buffer2;

        std::lock_guard<std::mutex> lock(m);
        command1 = buffer1;
        command2 = buffer2;
    }
}

void Game::parse()
{
    std::lock_guard<std::mutex> lock(m);

    if (command1.empty())
        return;

    if (command1 == "kick")
    {
        std::string nick = command2;
        sendJoinError(ErrorCodes::Kick, players.at(nick).address, players.at(nick).port);
        players.erase(nick);
    }
    else if (command1 == "ban")
    {
        std::string nick = command2;
        sendJoinError(ErrorCodes::IpBan, players.at(nick).address, players.at(nick).port);
        banlist.push_back(players.at(nick).address.toString());
        banlist_f.clear();
        banlist_f << players.at(nick).address.toString() << endl;
        banlist_f.flush();
        players.erase(nick);
    }
    else if (command1 == "exit" || command1 == "quit")
    {
        quit = true;
    }
    else
    {
        cerr << "unknown command" << endl;
    }

    command1.clear();
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

    packet >> nickname >> ID >> password >> version;

    if (version != GAME_VERSION)
    {
        packet.clear();
        packet << static_cast<sf::Uint8>(NetCodes::JoinError) << static_cast<sf::Uint8>(ErrorCodes::InvalidVersion) << std::string(GAME_VERSION);
        UDPsocket.send(packet, address, port);
        return;
    }

    if (players.find(nickname) != players.end())
    {
        sendJoinError(ErrorCodes::NicknameExists, address, port);
        return;
    }

    if (players.size() >= std::stoul(config.at("max_players")) || elapsed > sf::seconds(std::stoi(config.at("join_time"))))
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
    players.at(nickname).map_size = std::stoi(config.at("map_size"));
    players.at(nickname).speed = std::stoi(config.at("player_speed"));
    players.at(nickname).ID = ID;
    players.at(nickname).address = address;
    players.at(nickname).port = port;
    clog << "player " << nickname << " joined the game" << endl;
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
    players.at(nickname).crosshair_distance = std::clamp(crosshair_distance, 0.0f, surv::CROSS_CLAMP);
}

void Game::broadcast()
{
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
    UDPsocket.send(packet, address, port);
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
