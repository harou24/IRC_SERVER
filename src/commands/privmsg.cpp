#include "commands.hpp"

static std::string userPrivmsg(CmdController &controller, Client &sender, Client &receiver)
{
    std::string msg = controller.getParser().getArgument().arg2;
    std::string s = PRIV_MESSAGE(sender.getNick(), receiver.getNick(), sender.getUser(), sender.getHost(), msg);
    receiver.getStream().send(s, s.length());
    if (receiver.getAway())
        return std::string(RPL_AWAY(receiver.getNick(), sender.getNick(), receiver.getAwayMsg()));
    return "";
}

static std::string channelPrivmsg(CmdController &controller, std::string channel_name, Client &sender)
{
    std::string msg = controller.getParser().getArgument().arg2;
    std::set<std::string> channel = controller.getServer().getChannel(channel_name);
    for (std::set<std::string>::const_iterator it = channel.begin(); it != channel.end(); it++)
    {
        if (*it != sender.getNick() && *it != '@' + sender.getNick())
        {
            std::cout << sender.getNick() << std::endl;
            std::string name = *it;
            if (name[0] == '@')
                name = &name[1];
            Client *receiver = controller.getServer().getClientByName(name);
            std::string s = PRIV_MESSAGE(sender.getNick(), channel_name, sender.getUser(), sender.getHost(), msg);
            receiver->getStream().send(s, s.length());
        }
    }
    return "";
}

std::string    privmsg(CmdController* controller)
{
    std::string receiver_name = controller->getParser().getArgument().arg1;
    Client *sender = controller->getServer().getClientByStream(controller->getCurrentMsg()->getStreamPtr());
    Client *receiver = controller->getServer().getClientByName(receiver_name);
    if (receiver != NULL) 
        return userPrivmsg(*controller, *sender, *receiver);
    else if (controller->getServer().isChannel(receiver_name))
        return channelPrivmsg(*controller, receiver_name, *sender);
    return std::string(ERR_NOSUCHNICK(sender->getNick(), receiver_name));
}