#include "commands.hpp"

std::string    quit(const CmdController& controller)
{
    #if 1
        print("DEBUG", "QUIT");
    #endif
    Client *cl = controller.getServer().getClientByStream(controller.getCurrentMsg().getStreamPtr());
    std::string msg = controller.getParser().getArgument().arg1;
    controller.getServer().removeClient(cl, std::string(RPL_QUIT(cl, msg)));
    return "";
}