#include "commands.hpp"

static void     removeClient(CmdController &controller, std::string channel)
{
    Client *cl = controller.getServer().getClientByStream(controller.getCurrentMsg()->getStreamPtr());
    std::string reply;
    if (controller.getServer().isChannel(channel))
    {
        if (controller.getServer().isInChannel(channel, cl->getNick()))
        {
            controller.getServer().removeInChannel(channel, cl->getNick());
            reply = RPL_PART(cl, channel);
        }
        else
            reply = ERR_NOTONCHANNEL(cl->getNick(), channel);
    }
    else
        reply = ERR_NOSUCHCHANNEL(cl->getNick(), channel);
    cl->getStream().send(reply, reply.length());
}

std::string    part(CmdController* controller)
{
    std::string channels_list = controller->getParser().getArgument().arg1;

    size_t pos = 0;
    while ((pos = channels_list.find(',')) != std::string::npos)
    {
        std::string channel = channels_list.substr(0, pos);
        channels_list = &channels_list[pos + 1];
        removeClient(*controller, channel);
    }
    removeClient(*controller, channels_list);
    return "";
}