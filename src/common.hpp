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

using std::cin;
using std::cout;
using std::clog;
using std::cerr;
using std::endl;

namespace surv
{
    inline static
    float getDistance(float x1, float x2, float y1, float y2)
    {
        return std::sqrt(std::pow((x1 - x2), 2) + std::pow((y1 - y2), 2));
    }

    inline const unsigned int VIEW_DIM_X = 800;
    inline const unsigned int VIEW_DIM_Y = 800;
    inline const unsigned int DEFAULT_PLAYER_SPEED = 10;
    inline const unsigned int MAP_DIMENSION = 10000;
    inline const unsigned int MAX_PLAYERS = 100;
    inline const unsigned int MAX_BULLETS = 10000;
    inline const unsigned int SEND_DELAY = 50;
    inline const unsigned int JOIN_TIME = 60;
    inline const unsigned short DEFAULT_PORT = 7777;
    inline const double PI = std::acos(-1);
    inline const float CROSS_CLAMP = getDistance(VIEW_DIM_X, 0, VIEW_DIM_Y, 0);
    inline const std::string VERSION = "0.0.1";
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
    InvalidVersion,
    InvalidPassword,
    NicknameExists,
    Kick,
    IpBan
};
