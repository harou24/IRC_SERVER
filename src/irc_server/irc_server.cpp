#include "irc_server.hpp"
#include "cmd_controller.hpp"
#include "print.hpp"

IrcServer::IrcServer(int port, std::string password)
{
    _mServer = new Server(port, password);
}

IrcServer::~IrcServer()
{
    std::vector<Client *>::iterator it = _clients.begin();
    while (it != _clients.end())
    {
        delete *it;
        it++;
    }
}

void    IrcServer::start()
{
    _mServer->init();
    print("INFO", "starting server...");
    CmdController cmd(this);
    while (_mServer->isRunning())
    {
        _mServer->runOnce();
        while (Message *msg = &_mServer->getNextMsg())
        {
            if (msg)
            {
                #if 1
                    print("DEBUG", "incoming msg - " + msg->getData());
                #endif
                cmd.execute(msg);
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
    std::vector<Client *>::const_iterator it = _clients.begin();
    while (it != _clients.end())
    {
        if ((*it)->getNick() == nickname)
            return true;
        it++;
    }
    return false;
}

Client* IrcServer::getClientByName(std::string name)
{
    std::vector<Client *>::const_iterator it = clients_.begin();
    while (it != clients_.end())
    {
        if ((*it)->getNick() == name)
            return *it;
        it++;
    }
    return NULL;
}

Client* IrcServer::getClientByStream(TcpStream *stream)
{
    std::vector<Client *>::const_iterator it = _clients.begin();
    while (it != _clients.end())
    {
        if ((*it)->getStream() == *stream)
            return *it;
        it++;
    }
    return NULL;
}

void IrcServer::addClient(Client *cl)
{
    _clients.push_back(cl);
}

void IrcServer::removeClient(Client *cl)
{
    std::vector<Client *>::iterator it = _clients.begin();
    while (it != _clients.end())
    {
        if (*it == cl)
            break;
        it++;
    }
    if (it != _clients.end())
        _clients.erase(it);
}

void IrcServer::stop(void)
{
    std::cout << "Stopping server...\n";
     _mServer->stop();
}

bool IrcServer::isRunning(void) const { return _mServer->isRunning(); }