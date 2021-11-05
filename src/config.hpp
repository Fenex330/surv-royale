/* Store all global defines and constants here */

#pragma once

#ifdef _WIN32
    #define GAMEDATA_PATH "GameData.tar"
    #define SERVER_CONF_PATH "server.conf"
#else
    #define GAMEDATA_PATH "/usr/local/share/SurvRoyale/GameData.tar"
    #define SERVER_CONF_PATH "/usr/local/share/SurvRoyale/server.conf"
#endif

namespace surv
{
    inline const double PI = 3.14159265359;
    inline const unsigned int VIEW_DIM_X = 800;
    inline const unsigned int VIEW_DIM_Y = 800;
    inline const unsigned int DEFAULT_PLAYER_SPEED = 10;
    inline const unsigned int DEFAULT_PORT = 7777;
    inline const unsigned int MAP_DIMENSION = 1000;
    inline const unsigned int MAX_PLAYERS = 100;
    inline const unsigned int MAX_BULLETS = 50000;
}

enum class NetCodes
{
    RegisterRequest,
    RegisterResponse,
    PlayersList,
    Bullets,
    MoveAndRotate,
    Fire
};
