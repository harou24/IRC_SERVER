#include "commands.hpp"

std::string     away(CmdController* controller)
{
    TcpStream *stream = controller->getCurrentMsg()->getStreamPtr();
    Client *cl = controller->getServer()->getClientByStream(stream);
    std::string msg = controller->getParser().getArgument().arg1;

    if (cl)
    {
        if (msg != "")
        {
            std::string s = RPL_NOAWAY();
            cl->setAway(true);
            cl->setAwayMsg(msg);
            return s;
        }
        else if (cl->getAway())
        {
            std::string s = RPL_UNAWAY();
            cl->setAway(false);
            cl->setAwayMsg("");
            return s;
        }
    }
    return "";
}