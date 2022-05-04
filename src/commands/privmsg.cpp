#include "commands.hpp"

std::string    privmsg(CmdController* controller)
{
    std::string receiver_name = controller->getParser().getArgument().arg1;
    std::string msg = controller->getParser().getArgument().arg2;
    Client *sender = controller->getServer().getClientByStream(controller->getCurrentMsg()->getStreamPtr());
    Client *receiver = controller->getServer().getClientByName(receiver_name);
    if (receiver != NULL) 
    {
        std::string s = PRIV_MESSAGE(sender->getNick(), receiver_name, sender->getUser(), sender->getHost(), msg);
    	receiver->getStream().send(s, s.length());
        if (receiver->getAway())
            return std::string(RPL_AWAY(receiver->getNick(), sender->getNick(), receiver->getAwayMsg()));
    }
    return ("");
}