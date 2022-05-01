#pragma once

#include "headers.hpp"

class Manager
{
public:

    std::vector<std::thread> pool;
    std::mutex m;

    std::fstream config_f;
    std::fstream banlist_f;

    static std::unordered_map<std::string, std::string> config;
    static std::unordered_set<std::string> banlist;
    static std::string command1;
    static std::string command2;
    static std::atomic<bool> quit;

    Manager();

    void run();
    void scan();
    void parse();
};
