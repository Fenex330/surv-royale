#include "headers.hpp"

/* any static property of any server class must be declared either atomic or const for thread safety reasons */

int main()
{
    Game game;
    game.run();
    return 0;
}
