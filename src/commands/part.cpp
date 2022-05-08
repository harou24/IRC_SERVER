#include "commands.hpp"

static void sendReplyPart(const CmdController& controller, std::set<std::string> &channel, std::string msg)
{
    for(std::set<std::string>::const_iterator it = channel.begin(); it != channel.end(); it++)
    {
        std::string name = *it;
        if (name[0] == '@')
            name = &name[1];
        Client *receiver = controller.getServer().getClientByName(name);
        receiver->getStream().send(msg, msg.length());
    }
}

static void     removeClient(const CmdController& controller, std::string channel)
{
    Client *cl = controller.getServer().getClientByStream(controller.getCurrentMsg().getStreamPtr());
    std::string reply;
    if (controller.getServer().isChannel(channel))
    {
        if (controller.getServer().isInChannel(channel, cl->getNick()))
        {
            if (cl->getNick()[0] == '@')
                controller.getServer().removeInChannel(channel, '@' + cl->getNick());
            else
                controller.getServer().removeInChannel(channel, cl->getNick());
            reply = RPL_PART(cl, channel);
            sendReplyPart(controller, controller.getServer().getChannel(channel), reply);
        }
        else
            reply = ERR_NOTONCHANNEL(cl->getNick(), channel);
    }
    else
        reply = ERR_NOSUCHCHANNEL(cl->getNick(), channel);
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