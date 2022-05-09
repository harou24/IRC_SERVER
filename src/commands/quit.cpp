#include "commands.hpp"

static void     removeClientChannels(Client &cl, const CmdController& controller)
{
    std::map<std::string, Channel*> channels = controller.getServer().getAllChannels();
    for(std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); it++)
    {
        it->second->removeClient(cl);
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
    removeClientChannels(*cl, controller);
    controller.getServer().removeClient(cl);
    return "";
}