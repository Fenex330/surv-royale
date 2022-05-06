/* Store all global defines and constants here */

#pragma once

#ifdef _WIN32
    #define GAMEDATA_PATH "GameData.tar"
    #define SERVER_CONF_PATH "server.conf"
    #define BANLIST_PATH "banlist.txt"
    #define ID_PATH "ID"
#elif defined (APPIMAGE)
    #define GAMEDATA_PATH "share/SurvRoyale/GameData.tar"
    #define DEFAULT_SERVER_CONF_PATH "share/SurvRoyale/server.conf"
    #define SERVER_CONF_PATH "/.config/SurvRoyale/server.conf"
    #define BANLIST_PATH "/.config/SurvRoyale/banlist.txt"
    #define ID_PATH "/tmp/ID"
#else
    #define GAMEDATA_PATH "/usr/local/share/SurvRoyale/GameData.tar"
    #define DEFAULT_SERVER_CONF_PATH "/usr/local/share/SurvRoyale/server.conf"
    #define SERVER_CONF_PATH "/.config/SurvRoyale/server.conf"
    #define BANLIST_PATH "/.config/SurvRoyale/banlist.txt"
    #define ID_PATH "/tmp/ID"
#endif

#define CONFIG_DIR "/.config/SurvRoyale"

using std::cin;
using std::cout;
using std::clog;
using std::cerr;
using std::endl;

using namespace std::literals::chrono_literals;
namespace fs = std::filesystem;

namespace surv
{
    inline static
    float getDistance(float x1, float x2, float y1, float y2)
    {
        return std::sqrt(std::pow((x1 - x2), 2) + std::pow((y1 - y2), 2));
    }

    inline static
    int getRandom(int lowest, int highest)
    {
        thread_local std::random_device dev;
        thread_local std::mt19937 rng (dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist (lowest, highest);
        return dist(rng);
    }

    inline const unsigned int VIEW_DIM_X = 800;
    inline const unsigned int VIEW_DIM_Y = 800;
    inline const unsigned int SEND_DELAY = 50;
    inline const unsigned int PLAYER_RADIUS = 33;
    inline const double HEADSHOT_CHANCE = 0.15;
    inline const double PI = std::acos(-1);
    inline const float FOV = getDistance(VIEW_DIM_X, 0, VIEW_DIM_Y, 0) / 2.0f;
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
