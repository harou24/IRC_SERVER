#include "commands.hpp"

std::string    mode(const CmdController& controller)
{
    #if 1
        print("DEBUG", "MODE");
    #endif
    return std::string(RPL_UMODEIS(controller.getParser().getArgument().arg1, controller.getParser().getArgument()));
}