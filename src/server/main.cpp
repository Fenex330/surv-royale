#include "headers.hpp"

/* any static var must be declared either atomic or const or protected by mutex for thread safety reasons. Prefer thread_local instead */

int main()
{
    Manager manager;
    manager.run();
    return 0;
}
