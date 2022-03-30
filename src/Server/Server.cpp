#include "Server.hpp"

Server::Server(int port, std::string password) : _mAcceptor(port, HOST), _mClients(MAX_CLIENTS) {
    _mIsRunning = true;
    _mPassword = password;
}

Server::~Server(){
    _mClients.clear();
}

void            Server::start(){
    _mAcceptor.init();
    MultiClientHandler::addFdToSet(_mAcceptor.getListenSd());
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
    char            buffer[256];

    if ((len = receiveData(fd - FD_CORRECTION, buffer, sizeof(buffer))) > 0){
        buffer[len] = '\0';
        std::cout << "received: " << buffer << std::endl;
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