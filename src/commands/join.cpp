#include "commands.hpp"

static std::string  modeHandler(Channel& channel, Client& cl, const CmdController& controller)
{
    char modus = channel.getMode().getModus();
    std::string reply = "";
    std::string password = controller.getParser().getArgument().arg2;

    if (modus & (1<<4) && channel.getMode().getClientLimit() <= channel.NbrClients())
        return std::string(ERR_CHANNELISFULL(cl.getNick(), channel.getChannelName()));
    if (channel.getMode().isBan(cl.getNick()) && !channel.getMode().isInvite(cl))
        return std::string(ERR_BANNEDFROMCHAN(cl.getNick(), channel.getChannelName()));
    if (modus & (1<<1) && !channel.getMode().isInvite(cl))
        return std::string(ERR_INVITEONLYCHAN(cl.getNick(), channel.getChannelName()));
    if (modus & (1<<6) && channel.getMode().getPassword() != password && !channel.getMode().isInvite(cl))
        return std::string(ERR_BADCHANNELKEY(cl.getNick(), channel.getChannelName()));
    channel.addClient(cl);
    return "";
}

std::string         join(const CmdController& controller)
{
    #if 1
        print("DEBUG", "JOIN");
    #endif

    Client *cl = controller.getServer().getClientByStream(controller.getCurrentMsg().getStreamPtr());
    std::string channel_name = controller.getParser().getArgument().arg1;

    if (!controller.getServer().isChannel(channel_name))
        controller.getServer().addChannel(channel_name, *cl, (unsigned)time(NULL));
    Channel *channel = &controller.getServer().getChannel(channel_name);
    std::string reply = modeHandler(*channel, *cl, controller);
    if (!reply.empty())
        return reply;
    channel->sendMessage(*cl, std::string(RPL_JOIN(cl, channel_name)));
    
    std::string topic_reply = "";
    if (!channel->getMode().getTopic().topic.empty())
    {
        topic_reply = std::string(RPL_TOPIC(cl->getNick(), channel_name, channel->getMode().getTopic().topic));
        topic_reply += std::string(RPL_TOPICWHOTIME(cl->getNick(), channel_name, channel->getMode().getTopic()));
    }
    return std::string(RPL_JOIN(cl, channel_name) + topic_reply + RPL_NAMREPLY(cl->getNick(), channel_name) + channel->getNames() + "\n" + RPL_ENDOFNAMES(cl->getNick(), channel_name));
}
