#include "Server.hpp"

Server::Server(int port, std::string password) : _mAcceptor(port, HOST), _mClients(0) {
    _mIsRunning = false;
    _mPassword = password;
}

Server::~Server(){
    _mClients.clear();
}

void            Server::start(){
    _mAcceptor.init();
    MultiClientHandler::addFdToSet(_mAcceptor.getListenSd());
    _mIsRunning = true;
    std::cout << "RUNNING -> " << _mIsRunning << "\n";
    if(_mIsRunning){
        for (size_t i = 0; i <= MultiClientHandler::getFdmax(); i++){
            if (MultiClientHandler::isFdReadyToCommunicate(i)){
                if (isClientConnecting(i))
                    addClient();
                else
                    handleData(i);
            }
        }
    }
}

void            Server::stop(){
    _mIsRunning = false;
    exit(1);
}

void            Server::addClient(){
    TcpStream *newStream = _mAcceptor.accept();
    if (newStream->getSd() - FD_CORRECTION >= MAX_CLIENTS){
        std::cout << "no space left for another client....\n";
        return;
    }
    MultiClientHandler::addFdToSet(newStream->getSd());
    _mClients[newStream->getSd() - FD_CORRECTION] = newStream;
}

void            Server::removeClient(int fd){
    MultiClientHandler::clearFd(fd);
    _mClients[fd - FD_CORRECTION] = NULL;
    close(fd);
}

void            Server::handleData(int fd){
    size_t          len;
    char            buffer[512];

    if ((len = receiveData(fd - FD_CORRECTION, buffer, sizeof(buffer))) > 0){
        buffer[len] = '\0';
        _mQueue.push(createMessage(buffer, fd - FD_CORRECTION));
        sendData(fd - FD_CORRECTION, buffer, len);
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

std::ostream&   operator<<(std::ostream& o, Server const& src){
    for (int i = 0; i < MAX_CLIENTS; i++){
        if (src.getClients()[i] != NULL)
            o << *(src.getClients()[i]) << std::endl;
    }
    return o;
}