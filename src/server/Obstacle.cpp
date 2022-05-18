#include "headers.hpp"

Obstacle::Obstacle(int map_size, int radius, sf::Int16 hp) : map_size (map_size), radius (radius), hp (hp)
{
    rotation = double(surv::getRandom(0, 360));
    x = surv::getRandom(0, map_size);
    y = surv::getRandom(0, map_size);
}
