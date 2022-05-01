#include "headers.hpp"

std::unordered_map<std::string, std::string> Manager::config;
std::unordered_set<std::string> Manager::banlist;
std::string Manager::command1;
std::string Manager::command2;
std::atomic<bool> Manager::quit (false);

Manager::Manager()
{
    clog << "SurvRoyale version " << GAME_VERSION << endl;

    #ifdef _WIN32
        config_f.open(SERVER_CONF_PATH, std::ios::in);
        banlist_f.open(BANLIST_PATH, std::ios::in | std::ios::out | std::ios::app);
    #else
        const std::string HOME = std::getenv("HOME");

        if (!fs::exists(HOME + CONFIG_DIR))
            fs::create_directory(HOME + CONFIG_DIR);

        if (!fs::exists(HOME + SERVER_CONF_PATH))
            fs::copy_file(DEFAULT_SERVER_CONF_PATH, HOME + SERVER_CONF_PATH);

        config_f.open(HOME + SERVER_CONF_PATH, std::ios::in);
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
    {
        pool.push_back(std::thread([](int id){Game game (id); game.run();}, i));
        pool.back().detach();
    }
}

void Manager::run()
{
    while (!quit)
    {
        scan();
        parse();
    }
}

void Manager::scan()
{
    std::string buffer1;
    std::string buffer2;
    cin >> buffer1 >> buffer2;

    std::lock_guard<std::mutex> lock (m);
    command1 = buffer1;
    command2 = buffer2;
}

void Manager::parse()
{
    if (command1.empty())
        return;

    if (command1 == "exit" || command1 == "quit")
    {
        quit = true;
    }
    else
    {
        cerr << "unknown command" << endl;
    }

    command1.clear();
}
