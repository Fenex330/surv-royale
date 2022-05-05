#include "headers.hpp"

std::unordered_map<std::string, std::string> Manager::config;
std::unordered_set<std::string> Manager::banlist;

std::string Manager::command1;
std::string Manager::command2;

std::atomic<bool> Manager::quit (false);
std::atomic<int> Manager::id (0);

std::fstream Manager::banlist_f;
std::mutex Manager::m;

Manager::Manager()
{
    clog << "SurvRoyale version " << GAME_VERSION << endl;

    #ifdef _WIN32
        std::fstream config_f (SERVER_CONF_PATH, std::ios::in);
        banlist_f.open(BANLIST_PATH, std::ios::in | std::ios::out | std::ios::app);
    #else
        const std::string HOME = std::getenv("HOME");

        if (!fs::exists(HOME + CONFIG_DIR))
            fs::create_directory(HOME + CONFIG_DIR);

        if (!fs::exists(HOME + SERVER_CONF_PATH))
            fs::copy_file(DEFAULT_SERVER_CONF_PATH, HOME + SERVER_CONF_PATH);

        std::fstream config_f (HOME + SERVER_CONF_PATH, std::ios::in);
        banlist_f.open(HOME + BANLIST_PATH, std::ios::in | std::ios::out | std::ios::app);
    #endif

    if (!config_f)
    {
        cerr << "server.conf open error" << endl;
        std::exit(1);
    }

    if (!banlist_f)
    {
        cerr << "banlist.txt open error" << endl;
        std::exit(1);
    }

    while (!config_f.eof())
    {
        std::string param;
        std::string value;
        config_f >> param >> value;
        config[param] = value;
    }

    while (!banlist_f.eof())
    {
        std::string line;
        std::getline(banlist_f, line);
        banlist.insert(line);
    }

    for (int i = 1; i <= std::stoi(config.at("max_matches")); i++)
        pool.push_back(std::thread([](int id){Game game (id); game.run();}, i));
}

Manager::~Manager()
{
    for (auto& t : pool)
        t.join();
}

void Manager::run()
{
    while (!quit)
        scan();
}

void Manager::scan()
{
    std::string buffer1, buffer2, buffer3;

    cin >> buffer1;

    if (buffer1 == "exit" || buffer1 == "quit")
    {
        quit = true;
        return;
    }

    cin >> buffer2;
    cin >> buffer3;

    std::lock_guard<std::mutex> lock (m);

    command1 = buffer1;
    command2 = buffer2;
    id = std::stoi(buffer3);
}
