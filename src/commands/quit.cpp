#include "commands.hpp"

static void     removeClientChannels(Client &cl, const CmdController& controller, std::string reply)
{
    std::map<std::string, Channel*> channels = controller.getServer().getAllChannels();
    for(std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); it++)
    {
        it->second->removeClient(cl, reply);
        if (!it->second->isActive())
            controller.getServer().removeChannel(it->first);
    }
}

std::string    quit(const CmdController& controller)
{
    #if 1
        print("DEBUG", "QUIT");
    #endif
    Client *cl = controller.getServer().getClientByStream(controller.getCurrentMsg().getStreamPtr());
    std::string msg = controller.getParser().getArgument().arg1;
    removeClientChannels(*cl, controller, std::string(RPL_QUIT(cl, msg)));
    controller.getServer().removeClient(cl);
    return "";
}