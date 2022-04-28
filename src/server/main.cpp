#include "headers.hpp"

/* any static var must be declared either atomic or const for thread safety reasons. Prefer thread_local instead */

int main()
{
    Game game;
    game.run();
    return 0;
}
