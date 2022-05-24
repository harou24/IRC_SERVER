#include "server.hpp"

#include <sstream>

# define MAXclients_ 5

Server::Server(int port, std::string password, std::string host) : acceptor_(port, host), clients_ss_(), nbrClients_(0)
{
    isRunning_ = false;
    password_ = password;
    #undef HOST
    #define HOST host
}

Server::~Server()
{
    std::map<int, TcpStream*>::iterator it = clients_ss_.begin();
    while (it != clients_ss_.end())
    {
        delete it->second;
        it++;
    }
    clients_ss_.clear();
    while (!queue_.empty())
    {
        Message *m = queue_.front();
        delete m;
        queue_.pop();
    }
}

void            Server::init()
{
    acceptor_.init();
    MultiClientHandler::addFdToSet(acceptor_.getListenSd());
    isRunning_ = true;
}

void            Server::runOnce()
{    
    if(isRunning_)
    {
        for (size_t fd = 0; fd <= MultiClientHandler::getFdmax(); fd++)
        {
            try{
                if (MultiClientHandler::isFdReadyToCommunicate(fd))
                {

                    if (isClientConnecting(fd) && nbrClients_ == MAXclients_)
                    {
                        disconnect(fd);
                        continue;

                    }
                    if (isClientConnecting(fd))
                        addClient();
                    else
                        handleData(fd);
                }
            }
            catch(std::exception &e)
            {
                print("ERROR", e.what());
                exit(1);
            }
        }
    }
}

void            Server::start(void)
{
    init();
    while (1)
    {
        if (!isRunning_) break;
        runOnce();
    }
}

void            Server::stop()
{
    isRunning_ = false;
}

Message& Server::getNextMsg(void)
{
    Message *msg = NULL;
    
    if (!queue_.empty())
    {
        msg = queue_.front();
        queue_.pop();
    }
    return *msg;
}

void            Server::addClient()
{
    if (nbrClients_ == MAXclients_)
    {
        print("ERROR", "no space left for another client....");
        return;
    }
    TcpStream *newStream = acceptor_.accept();
    MultiClientHandler::addFdToSet(newStream->getSd());
    clients_ss_.insert(std::make_pair(newStream->getSd(), newStream));
    std::cout << YELLOW << "New client with fd: " << newStream->getSd() << RESET << std::endl;
    nbrClients_++;
}

void            Server::removeClient(int fd)
{
    disconnect(fd);
    delete clients_ss_.at(fd);
    clients_ss_.erase(fd);
    std::cout << YELLOW << "Removing client with fd: " << fd << RESET << std::endl;
    nbrClients_--;
}

std::queue<std::string> Server::split(const std::string &data)
{
    std::queue<std::string> res;
    std::string line;
    for (std::stringstream stream(data ); std::getline(stream, line, '\n');)
    {
        res.push(line);
    }
    return res;
}

TcpStream*      Server::getStreamFromFd(int fd)
{
    TcpStream *stream  = NULL;
    std::map<int, TcpStream *>::iterator it = clients_ss_.find(fd);
    if (it != clients_ss_.end())
        stream = it->second;
    return stream;
}

void            Server::handleData(int fd)
{
    std::string data = receiveData(fd);
    if (data.length() == 0)
        queue_.push(new Message("EXIT", getStreamFromFd(fd)));
    else if (data[data.length() - 1] != '\n')
    {
        getStreamFromFd(fd)->addToBuffer(data);
        getStreamFromFd(fd)->setTimeStamp((unsigned)time(NULL));
    }
    else
    {
        if (data[data.length() - 1] == '\n')
        {
            data = getStreamFromFd(fd)->getBuffer() + data;
            getStreamFromFd(fd)->emptyBuffer();
        }
        std::queue<std::string> splited = split(data);
        if (!splited.empty())
        {
            while (!splited.empty())
            {
                std::string cmd = splited.front();
                queue_.push(new Message(cmd, getStreamFromFd(fd)));
                splited.pop();
            }
            getStreamFromFd(fd)->setTimeStamp((unsigned)time(NULL));
        }
        getStreamFromFd(fd)->setTimeStamp((unsigned)time(NULL));
    }
}

void            Server::sendData(int fd, char *buffer, size_t len)
{
    if (clients_ss_[fd])
        clients_ss_[fd]->send(buffer, len);
}

std::string          Server::receiveData(int fd)
{
    if (!clients_ss_[fd])
        return std::string("");

    char    buffer[512];
    size_t len = clients_ss_[fd]->receive(buffer, 512);
    buffer[len] = '\0';
    return std::string(buffer);
}

bool            Server::isClientConnecting(int fd)
{
    return fd == acceptor_.getListenSd();
}

const std::map<int, TcpStream*>&     Server::getClients() const
{
    return clients_ss_;
}

std::queue<Message *>&     Server::getQueue()
{
    return queue_;
}

std::string Server::getPassword(void) const { return password_; }

void Server::disconnect(int fd)
{
    close(fd);
    MultiClientHandler::clearFd(fd);
}

bool Server::isRunning(void) const { return isRunning_; }

int                     Server::getNbrClients() const
{
    return nbrClients_;
}

std::ostream&   operator<<(std::ostream& o, Server const& src)
{
    for (std::map<int, TcpStream*>::const_iterator it = src.getClients().begin(); it != src.getClients().end(); it++)
        o << it->second << std::endl;
    o << "nbr " << src.getNbrClients() << std::endl;
    return o;
}