#include "commands.hpp"

std::string    user(CmdController* controller)
{
    TcpStream *stream = controller->getCurrentMsg()->getStreamPtr();
    Client *cl = controller->getServer().getClientByStream(stream);

    if (cl)
    {
        Args args = controller->getParser().getArgument();
        cl->setUser(args.arg1);
        cl->setHost(args.arg2);
        cl->setServer(args.arg3);
        cl->setReal(args.arg4);
    }
    return ("");
}