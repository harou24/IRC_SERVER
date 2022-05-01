#include "commands.hpp"

std::string    ping(CmdController* controller)
{
    if (controller)
        std::cout << "PING : " << controller->getParser().getArgument().arg1 << std::endl;
    return std::string("PING : " + controller->getParser().getArgument().arg1);
}