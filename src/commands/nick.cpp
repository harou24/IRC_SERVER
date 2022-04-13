#include "commands.hpp"


std::string    nick(IrcServer* s)
{
    if (s)
        std::cout << "nick cmd!\n";
    return std::string("Reply\n");
}

