/* Store all global defines and constants here */

#pragma once

#include <iostream>
#include <cmath>

#define LOG(X) std::cout << X << std::endl

namespace surv
{
    inline constexpr long double PI = std::acos(-1);
    inline const int VIEW_DIM_X = 800;
    inline const int VIEW_DIM_Y = 800;
    inline const int DEFAULT_PLAYER_SPEED = 10;
}
