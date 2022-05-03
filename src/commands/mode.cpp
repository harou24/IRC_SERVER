#include "commands.hpp"

std::string    mode(CmdController* controller)
{
    #if 1
    if (controller)
        print("DEBUG", "MODE");
    #endif
    return std::string(RPL_UMODEIS(controller->getParser().getArgument().arg1, controller->getParser().getArgument()));
}