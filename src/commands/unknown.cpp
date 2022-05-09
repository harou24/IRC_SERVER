#include "commands.hpp"


std::string    unknown(const CmdController& controller)
{
    (void)controller;
    return std::string("UNKNOWN\n");
}