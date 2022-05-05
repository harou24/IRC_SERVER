#include "server.hpp"

#include <sstream>

Server::Server(int port, std::string password) : _mAcceptor(port, HOST), _clientsss(), _mNbrClients(0) {
    _mIsRunning = false;
    _mPassword = password;
}

Server::~Server(){
    std::map<int, TcpStream*>::iterator it = _clientsss.begin();
    while (it != _clientsss.end())
    {
        delete it->second;
        it++;
    }
    _clientsss.clear();
    while (!_mQueue.empty())
    {
        Message *m = _mQueue.front();
        delete m;
        _mQueue.pop();
    }
}

void            Server::init(){
    _mAcceptor.init();
    MultiClientHandler::addFdToSet(_mAcceptor.getListenSd());
    _mIsRunning = true;
}

void            Server::runOnce(){    
    if(_mIsRunning){
        for (size_t fd = 0; fd <= MultiClientHandler::getFdmax(); fd++){
            try{
                if (MultiClientHandler::isFdReadyToCommunicate(fd)){
                    if (isClientConnecting(fd))
                        addClient();
                    else
                        handleData(fd);
                }
            }
            catch(std::exception &e){
                std::cout << e.what() << "FD->" << fd << std::endl;
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
        if (!_mIsRunning) break;
        runOnce();
    }
}

void            Server::stop(){
    _mIsRunning = false;
}

Message& Server::getNextMsg(void)
{
    Message *msg = NULL;
    
    if (!_mQueue.empty())
    {
        msg = _mQueue.front();
        _mQueue.pop();
    }
    return *msg;
}

void            Server::addClient(){
    if (_mNbrClients == MAX_CLIENTS){
        std::cout << "no space left for another client....\n";
        return;
    }
    TcpStream *newStream = _mAcceptor.accept();
    MultiClientHandler::addFdToSet(newStream->getSd());
    _clientsss.insert(std::make_pair(newStream->getSd(), newStream));
    _mNbrClients++;
}

void            Server::removeClient(int fd){
    MultiClientHandler::clearFd(fd);
    delete _clientsss.at(fd);
    _clientsss.erase(fd);
    close(fd);
    _mNbrClients--;
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
    std::map<int, TcpStream *>::iterator it = _clientsss.find(fd);
    if (it != _clientsss.end())
        stream = it->second;
    return stream;
}

void            Server::handleData(int fd){
    std::string data = receiveData(fd);
    std::queue<std::string> splited = split(data);
    if (!splited.empty())
    {
        while (!splited.empty())
        {
            std::string cmd = splited.front();
            _mQueue.push(new Message(cmd, getStreamFromFd(fd)));
            splited.pop();
        }
    }
    else
        removeClient(fd);
}

void            Server::sendData(int fd, char *buffer, size_t len){
    if (_clientsss[fd])
        _clientsss[fd]->send(buffer, len);
}

std::string          Server::receiveData(int fd)
{
    if (!_clientsss[fd])
        return std::string("");

    char    buffer[512];
    size_t len = _clientsss[fd]->receive(buffer, 512);
    buffer[len] = '\0';
    return std::string(buffer);
}

bool            Server::isClientConnecting(int fd){
    return fd == _mAcceptor.getListenSd();
}

const std::map<int, TcpStream*>&     Server::getClients() const{
    return _clientsss;
}

std::queue<Message *>&     Server::getQueue(){
    return _mQueue;
}

std::string Server::getPassword(void) const { return _mPassword; }

bool Server::isRunning(void) const { return _mIsRunning; }

int                     Server::getNbrClients() const{
    return _mNbrClients;
}

std::ostream&   operator<<(std::ostream& o, Server const& src){
    for (std::map<int, TcpStream*>::const_iterator it = src.getClients().begin(); it != src.getClients().end(); it++)
        o << it->second << std::endl;
    o << "nbr " << src.getNbrClients() << std::endl;
    return o;
}