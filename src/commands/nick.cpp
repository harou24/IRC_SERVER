#include "commands.hpp"

std::string    nick(CmdController* controller)
{
    if (controller)
        std::cout << "nick cmd!\n";
    welcome(controller);
    return std::string("Reply\n");
}

