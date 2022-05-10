#include "commands.hpp"

std::string    join(const CmdController& controller)
{
    #if 1
        print("DEBUG", "JOIN");
    #endif

    Client *cl = controller.getServer().getClientByStream(controller.getCurrentMsg().getStreamPtr());
    std::string channel_name = controller.getParser().getArgument().arg1;

    if (!controller.getServer().isChannel(channel_name))
        controller.getServer().addChannel(channel_name, *cl);
    Channel *channel = &controller.getServer().getChannel(channel_name);
    std::cout << channel->Invite() << std::endl;
    if (channel->isInvite(*cl) || (!channel->Invite()))
        channel->addClient(*cl);
    else
        return std::string(ERR_INVITEONLYCHAN(cl->getNick(), channel_name));
    std::cout << "NAMES = " << channel->getNames() << std::endl;
    channel->sendMessage(*cl, std::string(RPL_JOIN(cl, channel_name)));
    
    return std::string(RPL_JOIN(cl, channel_name) + RPL_NAMREPLY(cl->getNick(), channel_name) + channel->getNames() + "\n" + RPL_ENDOFNAMES(cl->getNick(), channel_name));
}