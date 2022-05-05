#include "commands.hpp"

std::string getAllNamesChannel(std::set<std::string> &channel, std::string s, CmdController* controller)
{
    std::set<std::string>::const_iterator it = channel.begin();
    std::string names;
    Client *receiver = controller->getServer().getClientByName(*it);

    if (it != channel.end())
    {
        receiver->getStream().send(s, s.length());
        names = *it;
        it++;
    }
    
    for(; it != channel.end(); it++)
    {
        receiver = controller->getServer().getClientByName(*it);
        receiver->getStream().send(s, s.length());
        names += " " + *it;
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
        names = getAllNamesChannel(controller->getServer().getChannel(channel), RPL_JOIN(cl, channel), controller);
        controller->getServer().addInChannel(channel, cl->getNick());
    }

    return std::string(RPL_JOIN(cl, channel) + RPL_NAMREPLY(cl->getNick(), channel) + names + "\n" + RPL_ENDOFNAMES(cl->getNick(), channel));
}