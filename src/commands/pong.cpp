#include "commands.hpp"

std::string    pong(const CmdController& controller)
{
    srand((unsigned)time(NULL) * getpid());
    #if 1
            print("DEBUG", "PONG " + controller.getCurrentMsg().getData());
    #endif
    if (&controller.getParser().getArgument().arg1[1] == controller.getCurrentMsg().getStream().getPing())
    {
        controller.getCurrentMsg().getStream().setPing("");
        return std::string("");
    }
    Client* cl = controller.getServer().getClientByStream(controller.getCurrentMsg().getStreamPtr());
    controller.getServer().removeClient(cl, std::string(RPL_QUIT(cl, ":incorrect pong")));
    return std::string("");
}
