#include "irc_server.hpp"
#include "cmd_controller.hpp"

IrcServer::IrcServer(int port, std::string password)
{
    _mServer = new Server(port, password);
}

IrcServer::~IrcServer() 
{
}

void    IrcServer::start()
{
    _mServer->init();
    std::cout << "starting server...\n";
    CmdController cmd(this);
    while (1)
    {
        _mServer->runOnce();
        while (Message *msg = &_mServer->getNextMsg())
        {
            if (msg)
            {
                cmd.execute(msg);
                std::cout << "msg->" << msg->getData() << "\n"; 
                delete(msg);
            }
            else
            {
                break;
            }
        }
    }
}

bool IrcServer::isNickInUse(const std::string &nickname)
{
    std::vector<Client *>::const_iterator it = clients_.begin();
    while (it != clients_.end())
    {
        if ((*it)->getNick() == nickname)
            return true;
        it++;
    }
    return false;
}

Client* IrcServer::getClientByStream(TcpStream *stream)
{
    std::vector<Client *>::const_iterator it = clients_.begin();
    while (it != clients_.end())
    {
        if ((*it)->getStream() == *stream)
            return *it;
        it++;
    }
    return NULL;
}

void IrcServer::addClient(Client *cl)
{
    clients_.push_back(cl);
}

void IrcServer::removeClient(Client *cl)
{
    std::vector<Client *>::iterator it = clients_.begin();
    while (it != clients_.end())
    {
        if (*it == cl)
            break;
        it++;
    }
    if (it != clients_.end())
        clients_.erase(it);
}