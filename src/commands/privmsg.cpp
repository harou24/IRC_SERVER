#include "commands.hpp"

std::string    privmsg(CmdController* controller)
{
    if (controller)
        std::cout << "PRIVMSG" << std::endl;
    return std::string(":PRIVMSG " + controller->getParser().getArgument().arg1 + " " + controller->getParser().getArgument().arg2 + "\n");
}