#include "headers.hpp"

Obstacle::Obstacle(int map_size, int radius) : map_size (map_size), radius (radius)
{
    rotation = double(surv::getRandom(0, 360));
    x = surv::getRandom(1, map_size);
    y = surv::getRandom(1, map_size);
}
