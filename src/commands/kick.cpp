#include "commands.hpp"

std::string     kick(const CmdController& controller)
{
    std::cout << "KICK\n";
    Client *cl = controller.getServer().getClientByStream(controller.getCurrentMsg().getStreamPtr());
    std::string channel_name = controller.getParser().getArgument().arg1;
    if (controller.getServer().isChannel(channel_name))
    {
        Channel channel = controller.getServer().getChannel(channel_name);
        if (channel.isOperator(*cl))
        {
            if (channel.isInChannel(controller.getParser().getArgument().arg2))
            {
                std::string reply = RPL_KICK(cl, channel.getChannelName(), controller.getParser().getArgument().arg2, controller.getParser().getArgument().arg3);
                channel.removeClient(*controller.getServer().getClientByName(controller.getParser().getArgument().arg2), reply);
                controller.getServer().getClientByName(controller.getParser().getArgument().arg2)->getStream().send(reply, reply.length());

                // std::string reply_kicked = RPL_PART(controller.getServer().getClientByName(controller.getParser().getArgument().arg2), channel_name);
                // controller.getServer().getClientByName(controller.getParser().getArgument().arg2)->getStream().send(reply_kicked, reply_kicked.length());
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