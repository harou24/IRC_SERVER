#include "IrcServer.hpp"

IrcServer::IrcServer(int port, std::string password) : _mServer(port, password) {}

IrcServer::~IrcServer() {}

// void    startServer(int port, std::string password);
void    IrcServer::processMessage()
{
    while (1)
    {
        while (_mServer.getQueue().size() > 0)
        {

        }

        
    }
}