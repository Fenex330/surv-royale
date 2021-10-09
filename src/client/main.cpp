#include <SFML/GpuPreference.hpp>
#include "Game.hpp"

SFML_DEFINE_DISCRETE_GPU_PREFERENCE

int main()
{
    Game game;
    game.run();
    return 0;
}
