#include "commands.hpp"

std::string    invite(const CmdController& controller)
{
    #if 1
        print("DEBUG", "INVITE");
    #endif

    std::string receiver_name = controller.getParser().getArgument().arg1;
    std::string channel = controller.getParser().getArgument().arg2;
    Client *sender = controller.getServer().getClientByStream(controller.getCurrentMsg().getStreamPtr());
    Client *receiver = controller.getServer().getClientByName(receiver_name);
    if (receiver != NULL) 
    {
        std::string s = INVITE_MESSAGE(sender->getNick(), receiver_name, sender->getUser(), sender->getHost(), channel);
    	receiver->getStream().send(s, s.length());
        if (receiver->getAway())
            return std::string(RPL_AWAY(receiver->getNick(), sender->getNick(), receiver->getAwayMsg()));
        return std::string(RPL_INVITING(sender->getNick(),receiver_name,channel));
    }
    return std::string(ERR_NOSUCHNICK(sender->getNick(), receiver_name));
}