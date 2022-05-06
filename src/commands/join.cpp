#include "commands.hpp"

static void sendReplyJoin(CmdController* controller, std::set<std::string> &channel, std::string msg)
{
    for(std::set<std::string>::const_iterator it = channel.begin(); it != channel.end(); it++)
    {
        Client *receiver = controller->getServer().getClientByName(*it);
        receiver->getStream().send(msg, msg.length());
    }
}

static std::string getAllNamesChannel(std::set<std::string> &channel)
{
    std::string names = "";

    for(std::set<std::string>::const_iterator it = channel.begin(); it != channel.end(); it++)
    {
        if (names.length() > 0)
            names += " " + *it;
        else
            names = *it;
    }
    return names;
}

std::string    join(CmdController* controller)
{
    #if 1
    if (controller)
        print("DEBUG", "JOIN");
    #endif

    Client *cl = controller->getServer().getClientByStream(controller->getCurrentMsg()->getStreamPtr());
    std::string channel = controller->getParser().getArgument().arg1;
    std::string names;

    if (!controller->getServer().isChannel(channel))
        controller->getServer().addChannel(channel);
    if (!controller->getServer().isInChannel(channel, cl->getNick()))
    {
        names = getAllNamesChannel(controller->getServer().getChannel(channel));
        sendReplyJoin(controller, controller->getServer().getChannel(channel), RPL_JOIN(cl, channel));
        controller->getServer().addInChannel(channel, cl->getNick());
    }
    
    return std::string(RPL_JOIN(cl, channel) + RPL_NAMREPLY(cl->getNick(), channel) + names + "\n" + RPL_ENDOFNAMES(cl->getNick(), channel));
}