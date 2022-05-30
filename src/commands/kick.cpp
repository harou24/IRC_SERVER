#include "commands.hpp"

std::string     kick(const CmdController& controller)
{
    Client *cl = controller.getServer().getClientByStream(controller.getCurrentMsg().getStreamPtr());
    std::string channel_name = controller.getParser().getArgument().arg1;
    if (controller.getServer().isChannel(channel_name))
    {
        Channel *channel = &controller.getServer().getChannel(channel_name);
        if (channel->isOperator(*cl))
        {
            if (channel->isInChannel(controller.getParser().getArgument().arg2))
            {
                std::string reply = RPL_KICK(cl, channel->getChannelName(), controller.getParser().getArgument().arg2, controller.getParser().getArgument().arg3);
                Client *clientToKick = controller.getServer().getClientByName(controller.getParser().getArgument().arg2);
                channel->removeClient(*clientToKick, reply);
                clientToKick->getStream().send(reply, reply.length());
                return "";
            }
            else if (controller.getServer().isNickInUse(controller.getParser().getArgument().arg2))
                return std::string(ERR_USERNOTINCHANNEL(cl->getNick(), controller.getParser().getArgument().arg2, channel_name));
            else
                return std::string(ERR_NOSUCHNICK(cl->getNick(), controller.getParser().getArgument().arg2));
        }
        else
            return std::string(ERR_CHANOPRIVSNEEDED(cl->getNick(), channel_name));
    }
    return std::string(ERR_NOSUCHCHANNEL(cl->getNick(), channel_name));
}
