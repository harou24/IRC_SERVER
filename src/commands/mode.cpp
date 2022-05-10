#include "commands.hpp"

static std::string  channel_mode(Channel& channel, Args& arg, Client& cl)
{
    std::string reply = RPL_UMODEIS(arg.arg1, arg);
    if (arg.arg2 == "")
        return reply;
    if (channel.isOperator(cl))
    {
        channel.sendMessage(cl, reply);
        if (arg.arg2[0] == '+')
            channel.seton(&arg.arg2[1]);
        else if (arg.arg2[0] == '-')
            channel.setoff(&arg.arg2[1]);
    }
    else if (channel.isInChannel(cl.getNick()))
        reply = ERR_CHANOPRIVSNEEDED(arg.arg1);
    else
        reply = ERR_NOTONCHANNEL(cl.getNick(), arg.arg1);
    return reply;
}



std::string         mode(const CmdController& controller)
{
    #if 1
        print("DEBUG", "MODE");
    #endif
    Client *cl = controller.getServer().getClientByStream(controller.getCurrentMsg().getStreamPtr());
    std::string reply = RPL_UMODEIS(controller.getParser().getArgument().arg1, controller.getParser().getArgument());
    if (controller.getParser().getArgument().arg1[0] == '#')
    {
        if (controller.getServer().isChannel(controller.getParser().getArgument().arg1))
            reply = channel_mode(controller.getServer().getChannel(controller.getParser().getArgument().arg1), controller.getParser().getArgument(), *cl);
        else
            reply = ERR_NOSUCHCHANNEL(cl->getNick(), controller.getParser().getArgument().arg1);
    }
    else if (controller.getServer().getClientByName(controller.getParser().getArgument().arg1) == 0)
        reply = ERR_NOSUCHNICK(cl->getNick(), controller.getParser().getArgument().arg1);
    else if (cl->getNick() != controller.getParser().getArgument().arg1)
        reply = ERR_USERSDONTMATCH(controller.getParser().getArgument().arg1);
    return reply;
}