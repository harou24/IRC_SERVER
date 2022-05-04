#include "commands.hpp"

std::string    pong(CmdController* controller)
{
    srand((unsigned)time(NULL) * getpid());
    #if 1
        if (controller)
            print("DEBUG", "PONG");
    #endif
    return std::string("");
}