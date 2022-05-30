#include "commands.hpp"

static std::string userNotice(const CmdController& controller, Client &sender, Client &receiver)
{
    std::string msg = controller.getParser().getArgument().arg2;
    std::string s = NOTICE_MESSAGE(sender.getNick(), receiver.getNick(), sender.getUser(), sender.getHost(), msg);
    receiver.getStream().send(s, s.length());
    return "";
}

static std::string channelNotice(const CmdController& controller, std::string channel_name, Client &sender)
{
    std::string msg = controller.getParser().getArgument().arg2;
    Channel *channel = &controller.getServer().getChannel(channel_name);
    if (channel->getMode().getModus() & (1<<3) && !channel->isInChannel(sender.getNick()))
        return "";
    std::string full_msg = NOTICE_MESSAGE(sender.getNick(), channel_name, sender.getUser(), sender.getHost(), msg);
    channel->sendMessage(sender, std::string(NOTICE_MESSAGE(sender.getNick(), channel_name, sender.getUser(), sender.getHost(), msg)));
    return "";
}

std::string    notice(const CmdController& controller)
{
    print("DEBUG", "NOTICE");
    std::string receiver_name = controller.getParser().getArgument().arg1;
    Client *sender = controller.getServer().getClientByStream(controller.getCurrentMsg().getStreamPtr());
    Client *receiver = controller.getServer().getClientByName(receiver_name);
    if (receiver != NULL) 
        return userNotice(controller, *sender, *receiver);
    else if (controller.getServer().isChannel(receiver_name))
        return channelNotice(controller, receiver_name, *sender);
    return "";
}
