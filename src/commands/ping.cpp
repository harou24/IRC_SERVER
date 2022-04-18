#include "commands.hpp"

std::string    ping(CmdController* controller)
{
    if (controller)
        std::cout << "PING\n";
    return std::string("");
}