#include "commands.hpp"

std::string    ping(const CmdController& controller)
{
    #if 1
            print("DEBUG", "PING");
    #endif
    return std::string("PONG " + controller.getParser().getArgument().arg1 + "\n");
}