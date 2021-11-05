#include "Game.hpp"

std::map<std::string, Player> Game::players;

Game::Game()
{
    UDPsocket.setBlocking(false);
    TCPsocket.setBlocking(false);
}

void Game::run()
{
    //
}
