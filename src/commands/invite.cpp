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
    if (controller.getServer().isChannel(channel))
    {
        if (receiver != NULL) 
        {
            if (!controller.getServer().getChannel(channel).isOperator(*sender))
                return std::string(ERR_CHANOPRIVSNEEDED(sender->getNick(),channel));
            controller.getServer().getChannel(channel).getMode().addInvite(*receiver);
            std::string s = INVITE_MESSAGE(sender->getNick(), receiver_name, sender->getUser(), sender->getHost(), channel);
            receiver->getStream().send(s, s.length());
            if (receiver->getAway())
                return std::string(RPL_AWAY(receiver->getNick(), sender->getNick(), receiver->getAwayMsg())) + std::string(RPL_INVITING(sender->getNick(),receiver_name,channel));
            return std::string(RPL_INVITING(sender->getNick(),receiver_name,channel));
        }
        return std::string(ERR_NOSUCHNICK(sender->getNick(), receiver_name));
    }
    return std::string(ERR_NOSUCHCHANNEL(sender->getNick(), sender->getNick()));
}
