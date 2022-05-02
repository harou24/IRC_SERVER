#include "commands.hpp"

std::string    pong(CmdController* controller)
{
    srand((unsigned)time(NULL) * getpid());
    if (controller)
        std::cout << "PONG\n";
    return std::string("");
}