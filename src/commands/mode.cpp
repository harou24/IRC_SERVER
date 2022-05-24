#include "commands.hpp"

template<typename T>
static std::string to_string(const T & value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

static std::string  ChannelMode(const CmdController& controller)
{
    Channel *channel = &controller.getServer().getChannel(controller.getParser().getArgument().arg1);
    Args    arg = controller.getParser().getArgument();
    Client *cl = controller.getServer().getClientByStream(controller.getCurrentMsg().getStreamPtr());
    std::string reply = "";

    if (arg.arg2 == "")
    {
        arg.arg3 = "+" + channel->getMode().isModeOn();
        reply = RPL_UMODEIS2(cl, arg);
        reply += RPL_CREATIONTIME(cl->getNick(), channel->getChannelName(), to_string(channel->getCreationTime()));
        return reply;
    }
    if (arg.arg2.find("+") == std::string::npos && arg.arg2.find("-") == std::string::npos)
        return "";
    if (channel->isOperator(*cl) || (arg.arg2 == "+b" && arg.arg3 == ""))
    {
        channel->getMode().setMode(controller, *cl, reply);
        if (reply == "")
            RPL_UMODEIS(cl, arg);
        if (!(arg.arg2 == "+b" && arg.arg3 == ""))
        {
            if (arg.arg2 == "+b")
            {
                arg.arg4 += "!*@*";
                reply = RPL_UMODEIS(cl, arg);
            }
            channel->sendMessage(*cl, reply);
        }
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