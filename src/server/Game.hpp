#pragma once

#include "headers.hpp"

class Game
{
public:

    sf::UdpSocket UDPsocket;
    sf::TcpSocket TCPsocket;
    sf::Packet packet;

    std::unordered_map<std::string, Player> players;
    std::vector<Player> players_pool (surv::MAX_PLAYERS);

    static bool quit;

    Game();
    ~Game();

    void run();
    void listen();
    void receiveJoinRequest();
    void receivePlayerInput();

    void broadcast();
    void send();
    void sendJoinError();
    void sendPlayersList();
    void sendProjectilesList();
    void sendObjectsList();
    void sendGameState();

    static void cleanup();
};
