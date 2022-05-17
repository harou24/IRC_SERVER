#include "commands.hpp"

std::string    pass(const CmdController& controller)
{
    std::string reply("");
    std::string password = controller.getParser().getArgument().arg1;
    TcpStream *stream = controller.getCurrentMsg().getStreamPtr();

    Client *cl = new Client("UNKNOWN", stream);
    cl->setPasswordUsedToConnect(password);
    controller.getServer().addClient(cl);
    if (!controller.getServer().isPasswordOk(password))
    {
        reply = ":127.0.0.1 NOTICE * :Password incorrect\n";
        std::cout << "---------PASSS INCORRECT-------------\n";
    }
    return reply;
}