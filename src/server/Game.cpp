#include "Game.hpp"

bool Game::quit = false;

Game::Game()
{
    UDPsocket.setBlocking(false);
    TCPsocket.setBlocking(false);

    if (UDPsocket.bind(surv::DEFAULT_PORT) != sf::Socket::Done)
        exit(1);
}

void Game::run()
{
    while (!quit)
    {
        //
    }
}
