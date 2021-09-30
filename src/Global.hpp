/* Store all global defines and constants here */

#pragma once

#include <iostream>

#define LOG(X) std::cout << X << std::endl

namespace surv
{
    inline const long double PI = 3.14159265359;
    inline const int VIEW_DIM_X = 800;
    inline const int VIEW_DIM_Y = 800;
    inline const int DEFAULT_PLAYER_SPEED = 10;
}
