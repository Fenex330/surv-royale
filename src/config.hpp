/* Store all global defines and constants here */

#pragma once

#ifdef _WIN32
    #define GAMEDATA_PATH "GameData.tar"
    #define SERVER_CONF_PATH "server.conf"
    #define BANLIST_PATH "banlist.txt"
#else
    #define GAMEDATA_PATH "/usr/local/share/SurvRoyale/GameData.tar"
    #define SERVER_CONF_PATH "/usr/local/share/SurvRoyale/server.conf"
    #define BANLIST_PATH "/usr/local/share/SurvRoyale/banlist.txt"
#endif

namespace surv
{
    inline const double PI = 3.14159265359;
    inline const unsigned short DEFAULT_PORT = 7777;
    inline const unsigned int VIEW_DIM_X = 800;
    inline const unsigned int VIEW_DIM_Y = 800;
    inline const unsigned int DEFAULT_PLAYER_SPEED = 10;
    inline const unsigned int MAP_DIMENSION = 1000;
    inline const unsigned int MAX_PLAYERS = 100;
    inline const unsigned int MAX_BULLETS = 50000;

    inline static
    float getDistance(float x1, float x2, float y1, float y2)
    {
        return std::sqrt(std::pow((x1 - x2), 2) + std::pow((y1 - y2), 2));
    }
}

/*
client-server handshake:
  1. client sends join request
  2. server replies back with 4 arrays (if successfull) (in loop) or error code (if unsuccessfull) (once)
  3. if receives arrays - client loads the game
  4. if receives error code - client displays it in message box
  5. after game load client should only send keyboard & mouse input state + chat message if any
*/

enum class NetCodes
{
    JoinRequest,
    PlayerInput,

    JoinError,
    PlayersList,
    ProjectilesList,
    ObjectsList,
    GameState
};

enum class ErrorCodes
{
    MapFull,
    IpBan,
    InvalidPassword,
    NicknameExists
};
