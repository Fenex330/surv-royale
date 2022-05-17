#include <SFML/GpuPreference.hpp>
#include "headers.hpp"

// on windows causes warnings that cannot be suppressed
SFML_DEFINE_DISCRETE_GPU_PREFERENCE

int main()
{
    Game game;
    game.run();
    return 0;
}
