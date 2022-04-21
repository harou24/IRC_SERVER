#include "irc_server.hpp"
#include "cmd_controller.hpp"

IrcServer::IrcServer(int port, std::string password) : _mServer(port, password) {}

IrcServer::~IrcServer() {}

void    IrcServer::start()
{
    _mServer.init();
    std::cout << "starting server...\n";
    CmdController cmd(this);
    while (1)
    {
        _mServer.runOnce();
        while (Message *msg = _mServer.getNextMsg())
        {
            if (msg)
            {
                std::cout << "Stream->" << msg->getStream() << std::endl;
                cmd.execute(msg);
                std::cout << "msg->" << msg->getData() << "\n"; 
            }
        }
    }
}
