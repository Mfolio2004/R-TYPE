#include <ostream>
#include <iostream>
#include "Core.hpp"

int main(void)
{
    R_TYPE::Core core;

    try {
        core.mainLoop();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}