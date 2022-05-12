#include "headers.hpp"

/* for thread safety reasons, any static variable must be declared either atomic, const, thread_local or protected by mutex */

int main()
{
    Manager manager;
    manager.run();
    return 0;
}
