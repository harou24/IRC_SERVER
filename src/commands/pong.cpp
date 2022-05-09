#include "commands.hpp"

std::string    pong(const CmdController& controller)
{
    srand((unsigned)time(NULL) * getpid());
    #if 1
            print("DEBUG", "PONG " + controller.getCurrentMsg().getData());
    #endif
    return std::string("");
}