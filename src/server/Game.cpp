#include "Game.hpp"

bool Game::quit = false;

Game::Game()
{
    UDPsocket.setBlocking(false);
    TCPsocket.setBlocking(false);
}

void Game::run()
{
    while (!quit)
    {
        //
    }
}
