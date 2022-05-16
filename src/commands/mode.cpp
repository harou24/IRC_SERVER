#include "commands.hpp"

static std::string  ChannelMode(const CmdController& controller)
{
    Channel *channel = &controller.getServer().getChannel(controller.getParser().getArgument().arg1);
    Args    arg = controller.getParser().getArgument();
    Client *cl = controller.getServer().getClientByStream(controller.getCurrentMsg().getStreamPtr());
    std::string reply = RPL_UMODEIS(cl, arg);

    if (arg.arg2 == "")
        return "";
    if (channel->isOperator(*cl) || (arg.arg2 == "+b" && arg.arg3 == ""))
    {
        channel->getMode().setMode(arg.arg2, arg.arg3, *cl, reply);
        if (!(arg.arg2 == "+b" && arg.arg3 == ""))
            channel->sendMessage(*cl, reply);
    }
    else if (channel->isInChannel(cl->getNick()))
        reply = ERR_CHANOPRIVSNEEDED(cl->getNick(), arg.arg1);
    else
        reply = ERR_NOTONCHANNEL(cl->getNick(), arg.arg1);
    return reply;
}



std::string         mode(const CmdController& controller)
{
    #if 1
        print("DEBUG", "MODE");
    #endif
    Client *cl = controller.getServer().getClientByStream(controller.getCurrentMsg().getStreamPtr());
    std::string reply = RPL_UMODEIS(cl, controller.getParser().getArgument());
    if (controller.getParser().getArgument().arg1[0] == '#')
    {
        if (controller.getServer().isChannel(controller.getParser().getArgument().arg1))
            reply = ChannelMode(controller);
        else
            reply = ERR_NOSUCHCHANNEL(cl->getNick(), controller.getParser().getArgument().arg1);
    }
    else if (controller.getServer().getClientByName(controller.getParser().getArgument().arg1) == 0)
        reply = ERR_NOSUCHNICK(cl->getNick(), controller.getParser().getArgument().arg1);
    else if (cl->getNick() != controller.getParser().getArgument().arg1)
        reply = ERR_USERSDONTMATCH(controller.getParser().getArgument().arg1);
    return reply;
}