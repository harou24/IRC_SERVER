#include "commands.hpp"

std::string    mode(const CmdController& controller)
{
    #if 1
        print("DEBUG", "MODE");
    #endif
    Client *cl = controller.getServer().getClientByStream(controller.getCurrentMsg().getStreamPtr());
    std::string reply = RPL_UMODEIS(controller.getParser().getArgument().arg1, controller.getParser().getArgument());
    if (controller.getParser().getArgument().arg1[0] == '#')
    {
        if (controller.getServer().isChannel(controller.getParser().getArgument().arg1))
        {
            if (controller.getParser().getArgument().arg2 == "")
                return reply;
            Channel *channel = &controller.getServer().getChannel(controller.getParser().getArgument().arg1);
            if (channel->isOperator(*cl))
                channel->sendMessage(*cl, reply);
            else if (channel->isInChannel(cl->getNick()))
                reply = ERR_CHANOPRIVSNEEDED(controller.getParser().getArgument().arg1);
            else
                reply = ERR_NOTONCHANNEL(cl->getNick(), controller.getParser().getArgument().arg1);
        }
        else
            reply = ERR_NOSUCHCHANNEL(cl->getNick(), controller.getParser().getArgument().arg1);
    }
    else if (controller.getServer().getClientByName(controller.getParser().getArgument().arg1) == 0)
        reply = ERR_NOSUCHNICK(cl->getNick(), controller.getParser().getArgument().arg1);
    else if (cl->getNick() != controller.getParser().getArgument().arg1)
        reply = ERR_USERSDONTMATCH(controller.getParser().getArgument().arg1);
    return reply;
}