#include "irc_server.hpp"
#include "cmd_controller.hpp"
#include "print.hpp"

IrcServer::IrcServer(int port, std::string password, std::string host)
{
    server_ = new Server(port, password, host);
}

IrcServer::~IrcServer()
{
    print("DEBUG", "IrcServer Destructor");
    for(std::vector<Client *>::iterator it = clients_.begin(); it != clients_.end(); it++)
        delete *it;
    clients_.clear();

    for (std::map<std::string, Channel*>::iterator it = channels_.begin(); it != channels_.end(); it++)
        delete it->second;
    channels_.clear();
}

void    IrcServer::WaitlistCheck()
{
    std::string error = "Error: closing connection because of registration timeout: 120seconds\n";
    unsigned int t = (unsigned)time(NULL);
    for (Waitlist::iterator it = clientsWaitlist_.begin(); it != clientsWaitlist_.end();)
    {
        Waitlist::iterator tmp = it;
        ++tmp;
        if (t - it->second >= 20)
        {
           int tmp = it->first->getStream().getSd();
            it->first->getStream().send(error, error.length());
            delete it->first;
            clientsWaitlist_.erase(it);
            server_->removeClient(tmp);
        }
        it = tmp;
    }
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
            if (msg->getData() != "EXIT")
            {
                #if 1
                    print("DEBUG", "incoming msg - " + msg->getData());
                #endif
                cmd.execute(msg);
                delete(msg);
            }
            else if (msg->getData() == "EXIT")
            {
                Client *cl = getClientByStream(msg->getStreamPtr());
                if (cl != NULL)
                    removeClient(cl, std::string(RPL_QUIT(cl, ":connection lost")));
                else
                {
                    Client *cl = getClientWaitlistByStream(msg->getStreamPtr());
                    removeClientWaitlist(cl);
                    server_->removeClient(msg->getStream().getSd());
                }
            }
            else
                break;
        }
        sendPing();
        WaitlistCheck();
    }
}

bool IrcServer::isNickInUse(const std::string &nickname)
{
    std::vector<Client *>::const_iterator it = clients_.begin();
    Waitlist::const_iterator itWait = clientsWaitlist_.begin();

    while (it != clients_.end())
    {
        if ((*it)->getNick() == nickname)
            return true;
        it++;
    }
    while (itWait != clientsWaitlist_.end())
    {
        if (itWait->first->getNick() == nickname)
            return true;
        itWait++;
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

Client* IrcServer::getClientWaitlistByStream(TcpStream *stream) const
{
    Waitlist::const_iterator it = clientsWaitlist_.begin();
    while (it != clientsWaitlist_.end())
    {
        if (it->first->getStream() == *stream)
            return it->first;
        it++;
    }
    return NULL;
}

void    IrcServer::addClient(Client *cl)
{
    clients_.push_back(cl);
}


void    IrcServer::addClientToWaitlist(Client* cl)
{
    clientsWaitlist_.insert(std::make_pair(cl, (unsigned)time(NULL)));
}


void IrcServer::removeClient(Client *cl, std::string reply)
{
    for(std::map<std::string, Channel*>::iterator it = channels_.begin(); it != channels_.end();)
    {
        std::map<std::string, Channel*>::iterator next = it;
        ++next;
        it->second->removeClient(*cl, reply);
        if (!it->second->isActive())
            removeChannel(it->first);
        it = next;
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
        server_->removeClient(cl->getStream().getSd());
        delete *it;
        clients_.erase(it);
    }
}

void    IrcServer::removeStream(TcpStream *stream)
{
    server_->removeClient(stream->getSd());
}

void    IrcServer::removeClientWaitlist(Client* cl)
{
    Waitlist::iterator it = clientsWaitlist_.begin();
    while (it != clientsWaitlist_.end())
    {
        if (it->first == cl)
            break;
        it++;
    }
    if (it != clientsWaitlist_.end())
    {
        delete it->first;
        clientsWaitlist_.erase(it);
    }
}

void    IrcServer::ConnectClient(Client* cl)
{
   Waitlist::iterator it = clientsWaitlist_.begin();
    while (it != clientsWaitlist_.end())
    {
        if (it->first == cl)
        {
            clientsWaitlist_.erase(it);
            addClient(cl);
            break;
        }    
        it++;
    }
}


bool    IrcServer::isChannel(std::string channel)
{
    for (std::string::iterator it = channel.begin(); channel.end() != it; ++it)
        *it = toupper(*it);

    if (channels_.find(channel) != channels_.end())
        return true;
    return false;
}

void    IrcServer::addChannel(std::string channel, Client &cl, unsigned int time)
{
    for (std::string::iterator it = channel.begin(); channel.end() != it; ++it)
        *it = toupper(*it);

    Channel *c = new Channel(channel, cl, time);
    channels_.insert(std::make_pair(channel, c));
}

void    IrcServer::removeChannel(std::string channel)
{
    for (std::string::iterator it = channel.begin(); channel.end() != it; ++it)
        *it = toupper(*it);

    Channel *tmp = &this->getChannel(channel);
    channels_.erase(channel);
    delete tmp;
}

Channel&    IrcServer::getChannel(std::string channel)
{
    for (std::string::iterator it = channel.begin(); channel.end() != it; ++it)
        *it = toupper(*it);
    return *channels_[channel];
}

void IrcServer::stop(void)
{
    print("DEBUG", "Stopping server");
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
