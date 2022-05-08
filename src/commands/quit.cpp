#include "commands.hpp"

std::string    quit(const CmdController& controller)
{
    #if 1
        print("DEBUG", "QUIT");
    #endif
    Client *cl = controller.getServer().getClientByStream(controller.getCurrentMsg().getStreamPtr());
    controller.getServer().removeClient(cl);
    return "";
}