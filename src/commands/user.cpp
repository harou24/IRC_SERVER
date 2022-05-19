#include "commands.hpp"

std::string    user(const CmdController& controller)
{
    std::string reply = "";
    TcpStream *stream = controller.getCurrentMsg().getStreamPtr();
    Client *cl = controller.getServer().getClientWaitListByStream(stream);

    if (cl)
    {
        Args args = controller.getParser().getArgument();
        cl->setUser(args.arg1);
        cl->setHost(args.arg2);
        cl->setServer(args.arg3);
        cl->setReal(args.arg4);
        controller.getServer().ConnectClient(cl);
        reply = welcome(cl->getNick(), args);
    }
    else if (controller.getServer().getClientByStream(stream) == NULL)
    {
        controller.getServer().removeStream(stream);
    }
    return reply;
}