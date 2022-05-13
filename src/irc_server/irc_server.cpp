#include "irc_server.hpp"
#include "cmd_controller.hpp"
#include "print.hpp"

IrcServer::IrcServer(int port, std::string password)
{
    std::cout << "CALL CONSTRUCTOR...\n";
    _mServer = new Server(port, password);
}

IrcServer::IrcServer(const IrcServer &server)
{
    std::cout << server._mNbclients<< "COPY CONSTRUCTOR...";
}

IrcServer::~IrcServer()
{
    for(std::vector<Client *>::iterator it = clients_.begin(); it != clients_.end(); it++)
    {
        std::cout << "REMOVING->" << *it << "\n";
        delete *it;
    }
    clients_.clear();

    for (std::map<std::string, Channel*>::iterator it = channels_.begin(); it != channels_.end(); it++)
        delete it->second;
    channels_.clear();
}

void    IrcServer::start()
{
    _mServer->init();
    print("INFO", "starting server...");
    CmdController cmd(*this);
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
                std::cout << "AFTER EXEC\n";
                delete(msg);
            }
            else
            {
                std::cout << "BREAKING...\n";
                break;
            }
            std::cout << "msg\n";
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

Client* IrcServer::getClientByName(std::string name) const
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

Client* IrcServer::getClientByStream(TcpStream *stream) const
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
    {
        delete *it;
        clients_.erase(it);
    }
}

bool    IrcServer::isChannel(std::string channel)
{
    if (channels_.find(channel) != channels_.end())
        return true;
    return false;
}

void    IrcServer::addChannel(std::string channel, Client &cl)
{
    Channel *c = new Channel(channel, cl);
    channels_.insert(std::make_pair(channel, c));
}

void    IrcServer::removeChannel(std::string channel)
{
    //LEAK
    Channel *tmp = &this->getChannel(channel);
    channels_.erase(channel);
    delete tmp;
}

Channel&    IrcServer::getChannel(std::string channel)
{
    return *channels_[channel];
}

std::map<std::string, Channel*>&    IrcServer::getAllChannels()
{
    return channels_;
}


void IrcServer::stop(void)
{
    std::cout << "Stopping server...\n";
     _mServer->stop();
}

bool IrcServer::isRunning(void) const { return _mServer->isRunning(); }

bool        IrcServer::isPasswordOk(const std::string &password) const
{
    return _mServer->getPassword() == password;
}
size_t    IrcServer::getNbClients(void) const { return clients_.size(); }
