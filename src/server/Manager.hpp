#pragma once

#include "headers.hpp"

class Manager
{
public:

    std::vector<std::thread> pool;

    static std::string command1;
    static std::string command2;

    static std::atomic<bool> quit;
    static std::atomic<int> id;

    static std::unordered_set<std::string> banlist;
    static std::fstream banlist_f;
    static std::mutex m;

    Manager();
    ~Manager();

    void run();
    void scan();
};
