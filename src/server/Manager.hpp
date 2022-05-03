#pragma once

#include "headers.hpp"

class Manager
{
public:

    std::vector<std::thread> pool;

    static std::unordered_map<std::string, std::string> config;
    static std::unordered_set<std::string> banlist;

    static std::string command1;
    static std::string command2;

    static std::atomic<bool> quit;
    static std::atomic<int> id;

    static std::fstream banlist_f;
    static std::mutex m;

    Manager();

    void run();
    void scan();
};
