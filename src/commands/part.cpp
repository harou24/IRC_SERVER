#include "commands.hpp"

static void     removeClient(const CmdController& controller, std::string channel_name)
{
    Client *cl = controller.getServer().getClientByStream(controller.getCurrentMsg().getStreamPtr());
    std::string reply;
    if (controller.getServer().isChannel(channel_name))
    {
        Channel *channel = &controller.getServer().getChannel(channel_name);
        if (channel->isInChannel(cl->getNick()))
        {
            reply = RPL_PART(cl, channel_name);
            channel->removeClient(*cl, reply);
            if (!channel->isActive())
                controller.getServer().removeChannel(channel_name);
        }
        else
            reply = ERR_NOTONCHANNEL(cl->getNick(), channel_name);
    }
    else
        reply = ERR_NOSUCHCHANNEL(cl->getNick(), channel_name);
    cl->getStream().send(reply, reply.length());
}

std::string    part(const CmdController& controller)
{
    std::string channels_list = controller.getParser().getArgument().arg1;

    size_t pos = 0;
    while ((pos = channels_list.find(',')) != std::string::npos)
    {
        std::string channel = channels_list.substr(0, pos);
        channels_list = &channels_list[pos + 1];
        removeClient(controller, channel);
    }
    removeClient(controller, channels_list);
    return "";
}
