#include "commands.hpp"


/*
    if 'L' set cehck current number of not bigger return err
    if user in ban mask return
    if user not in invite return and invite on
    if password is set blabalbla


    l   4
    b   5
    i   1
    k   6

    switch(opper_):

    case 4:
        if (nospace)
            return err;
    case 5:
        if (banned)
            return err;
    case 1:
        if isInvited || !invite
            continue
        else
            return err;
    case 6:
        if (key && keycorrect)
            conitinue;
        else
            return err;
    default:
        good;
    return ""
*/

static std::string  modeHandler(Channel& channel, Client& cl, const CmdController& controller)
{
    char modus = channel.getMode().getModus();
    std::string reply = "";
    std::string password = controller.getParser().getArgument().arg2;

    if (modus & (1<<4) && channel.getMode().getClientLimit() <= channel.NbrClients())
        return std::string(ERR_CHANNELISFULL(cl.getNick(), channel.getChannelName()));
    if (modus & (1<<5))
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
        controller.getServer().addChannel(channel_name, *cl);
    Channel *channel = &controller.getServer().getChannel(channel_name);
    std::string reply = modeHandler(*channel, *cl, controller);
    if (!reply.empty())
        return reply;
    std::cout << "NAMES = " << channel->getNames() << std::endl;
    channel->sendMessage(*cl, std::string(RPL_JOIN(cl, channel_name)));
    
    return std::string(RPL_JOIN(cl, channel_name) + RPL_NAMREPLY(cl->getNick(), channel_name) + channel->getNames() + "\n" + RPL_ENDOFNAMES(cl->getNick(), channel_name));
}