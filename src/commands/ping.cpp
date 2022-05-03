#include "commands.hpp"

std::string    ping(CmdController* controller)
{
    #if 1
        if (controller)
            print("DEBUG", "PING");
    #endif
    return std::string("PONG : " + controller->getParser().getArgument().arg1);
}