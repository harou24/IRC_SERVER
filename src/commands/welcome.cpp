#include "commands.hpp"

std::string    welcome(std::string nick, Args& args)
{
    std::string reply("");
    
    reply += RPL_WELCOME(nick, args);
    reply += RPL_YOURHOST(args);
    reply += std::string(RPL_CREATED);
    reply += std::string(LOGO_P1);
    reply += std::string(LOGO_P2);
    return reply;
}