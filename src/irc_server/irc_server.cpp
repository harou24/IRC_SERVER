#include "irc_server.hpp"
#include "cmd_controller.hpp"
#include "print.hpp"

IrcServer::IrcServer(int port, std::string password)
{
    std::cout << "CALL CONSTRUCTOR...\n";
    server_ = new Server(port, password);
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

void  IrcServer::sendPing()
{
    unsigned int t = (unsigned)time(NULL);
    for (size_t i = 0; i < clients_.size(); i++)
    {
        if (t - clients_[i]->getStream().getTimeStamp() >= 20 && clients_[i]->getStream().getPing().empty())
        {
            std::string ping = generateRandom(rand() % 10 + 5);
            std::string ping_reply = "PING :" + ping + "\n";
            clients_[i]->getStream().send(ping_reply, ping_reply.length());
            clients_[i]->getStream().setTimeStamp(t);
            clients_[i]->getStream().setPing(ping);
        }
        else if (t - clients_[i]->getStream().getTimeStamp() >= 20)
        {
            std::string error = "Error: closing connection because of ping timeout: 120seconds\n";
            clients_[i]->getStream().send(error, error.length());
            removeClient(clients_[i], std::string(RPL_QUIT(clients_[i], ":ping timout")));
        }
    }
}

void    IrcServer::start()
{
    server_->init();
    print("INFO", "starting server...");
    CmdController cmd(*this);
    while (server_->isRunning())
    {
        server_->runOnce();
        while (Message *msg = &server_->getNextMsg())
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
        sendPing();
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

void IrcServer::removeClient(Client *cl, std::string reply)
{
    for(std::map<std::string, Channel*>::iterator it = channels_.begin(); it != channels_.end(); it++)
    {
        it->second->removeClient(*cl, reply);
        if (!it->second->isActive())
            removeChannel(it->first);
    }

    std::vector<Client *>::iterator it = clients_.begin();
    while (it != clients_.end())
    {
        if (*it == cl)
            break;
        it++;
    }
    if (it != clients_.end())
    {
        disconnect(cl->getStream().getSd());
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

void    IrcServer::addChannel(std::string channel, Client &cl, unsigned int time)
{
    Channel *c = new Channel(channel, cl, time);
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
     server_->stop();
}

bool IrcServer::isRunning(void) const { return server_->isRunning(); }

bool        IrcServer::isPasswordOk(const std::string &password) const
{
    return server_->getPassword() == password;
}
size_t    IrcServer::getNbClients(void) const { return clients_.size(); }

void        IrcServer::disconnect(int fd)
{
    server_->disconnect(fd);
}
