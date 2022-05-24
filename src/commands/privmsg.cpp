#include "commands.hpp"

static std::string userPrivmsg(const CmdController& controller, Client &sender, Client &receiver)
{
    std::string msg = controller.getParser().getArgument().arg2;
    std::string s = PRIV_MESSAGE(sender.getNick(), receiver.getNick(), sender.getUser(), sender.getHost(), msg);
    receiver.getStream().send(s, s.length());
    if (receiver.getAway())
        return std::string(RPL_AWAY(receiver.getNick(), sender.getNick(), receiver.getAwayMsg()));
    return "";
}

static std::string channelPrivmsg(const CmdController& controller, std::string channel_name, Client &sender)
{
    std::cout << "PRIV CHAN MSG\n";
    std::string msg = controller.getParser().getArgument().arg2;
    Channel *channel = &controller.getServer().getChannel(channel_name);
    if (channel->getMode().isBan(sender.getNick()))
        return std::string(ERR_CANNOTSENDTOCHANBAN(sender.getNick(), channel_name));
    if (channel->getMode().getModus() & (1<<3) && !channel->isInChannel(sender.getNick()))
        return std::string(ERR_CANNOTSENDTOCHAN(sender.getNick(), channel_name));
    std::string full_msg = PRIV_MESSAGE(sender.getNick(), channel_name, sender.getUser(), sender.getHost(), msg);
    channel->sendMessage(sender, std::string(PRIV_MESSAGE(sender.getNick(), channel_name, sender.getUser(), sender.getHost(), msg)));
    return "";
}

std::string    privmsg(const CmdController& controller)
{
    std::string receiver_name = controller.getParser().getArgument().arg1;
    Client *sender = controller.getServer().getClientByStream(controller.getCurrentMsg().getStreamPtr());
    Client *receiver = controller.getServer().getClientByName(receiver_name);
    if (receiver != NULL) 
        return userPrivmsg(controller, *sender, *receiver);
    else if (controller.getServer().isChannel(receiver_name))
        return channelPrivmsg(controller, receiver_name, *sender);
    return std::string(ERR_NOSUCHNICK(sender->getNick(), receiver_name));
}