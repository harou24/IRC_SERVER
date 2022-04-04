#include "Server.hpp"
#include <assert.h>

Server::Server(int port, std::string password) : _mAcceptor(port, HOST), _mClients(0) {
    _mIsRunning = false;
    _mPassword = password;
}

Server::~Server(){
    _mClients.clear();
}

void            Server::start()
{
    _mAcceptor.init();
    MultiClientHandler::addFdToSet(_mAcceptor.getListenSd());

    _mIsRunning = true;
    while (_mIsRunning)
    {
        for (std::size_t fd = 3; fd <= MultiClientHandler::getFdmax(); fd++)
        {
            if (MultiClientHandler::isFdReadyToCommunicate(fd))
            {
                if (isClientConnecting(fd))
                {
                    if (_mNbClients < MAX_CLIENTS)
                        addClient();
                }
                else
                    handleData(fd);
            }
        }
    }
}

void            Server::stop()
{
    _mIsRunning = false;
    std::vector<TcpStream *>::iterator it = _mClients.begin();
    while (it != _mClients.end())
    {
        removeClient((*it)->getSd());
        it++;
    }
}

std::size_t Server::getIndexByFd(int fd)
{
    std::size_t i = 0;
    for ( ; i < _mNbClients; i++)
        if (_mClients[i]->getSd() == fd)
            break;
    return i;
}

void            Server::addClient(){
    TcpStream *newStream = _mAcceptor.accept();
    MultiClientHandler::addFdToSet(newStream->getSd());
    _mClients.push_back(newStream);
}

void            Server::removeClient(int fd){
    MultiClientHandler::clearFd(fd);
    _mClients.erase(_mClients.begin() + getIndexByFd(fd));
    close(fd);
}

void            Server::handleData(int fd){
    size_t          len;
    char            buffer[512];

    if ((len = receiveData(fd, buffer, sizeof(buffer))) > 0)
    {
        buffer[len] = '\0';
        _mQueue.push(createMessage(buffer, fd));
        sendData(fd, buffer, len);
    }
    else
        removeClient(fd);
}

void            Server::sendData(int fd, char *buffer, size_t len){
    _mClients[fd]->send(buffer, len);
}

size_t          Server::receiveData(int fd, char *buffer, size_t len){
    return _mClients[fd]->receive(buffer, len);
}

bool            Server::isClientConnecting(int fd){
    return fd == _mAcceptor.getListenSd();
}

const std::vector<TcpStream*>&     Server::getClients() const{
    return _mClients;
}

Message         Server::createMessage(std::string str, int fd){
    Message m = {str, _mClients[fd]};
    return m;
}

std::queue<Message>&     Server::getQueue(){
    return _mQueue;
}

std::string Server::getPassword(void) const { return _mPassword; }

bool Server::isRunning(void) const { return _mIsRunning; }

const TcpAcceptor& Server::getAcceptor(void) const { return _mAcceptor; }

std::ostream&   operator << (std::ostream& o, Server const& src){
    for (int i = 0; i < MAX_CLIENTS; i++){
        if (src.getClients()[i] != NULL)
            o << *(src.getClients()[i]) << std::endl;
    }
    return o;
}