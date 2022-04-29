#include "commands.hpp"


std::string    unknown(CmdController* controller)
{
    (void)controller;
    return std::string("UNKNOWN\n");
}