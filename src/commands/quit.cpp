#include "commands.hpp"

std::string    quit(CmdController* controller)
{
    #if 1
    if (controller)
        print("DEBUG", "QUIT");
    #endif
    Client *cl = controller->getServer()->getClientByStream(controller->getCurrentMsg()->getStreamPtr());
    controller->getServer()->removeClient(cl);
    return "";
}