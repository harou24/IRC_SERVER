#include "commands.hpp"

std::string    pass(const CmdController& controller)
{
    std::string reply("");
    std::string password = controller.getParser().getArgument().arg1;
    TcpStream *stream = controller.getCurrentMsg().getStreamPtr();

    Client *cl = new Client("UNKNOWN", stream);
    cl->setPasswordUsedToConnect(password);
    controller.getServer().addClientToWaitList(cl);
    if (!controller.getServer().isPasswordOk(password))
    {
        reply = ":" + std::string(HOST) + " NOTICE * :Password incorrect\n";
        print("DEBUG", reply);
    }
    return reply;
}