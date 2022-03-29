#include "Server.hpp"
# include <sys/select.h>

Server::Server(int port, std::string password) : _mAcceptor(port, HOST), _mClients(MAX_CLIENTS) {
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
    while(_mIsRunning){
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
}

void            Server::stopSigHandler(int pid){
    std::cout << "Stopping the server.... pid = " << pid << std::endl;
    _mIsRunning = false;
}

void            Server::addClient(){
    TcpStream *newStream = _mAcceptor.accept();
    if (newStream->getSd() - 4 >= MAX_CLIENTS){
        std::cout << "no space left for another client....\n";
        return;
    }
    MultiClientHandler::addFdToSet(newStream->getSd());
    std::cout << "FD = " << newStream->getSd() << std::endl;
    _mClients[newStream->getSd() - 4] = newStream;
}

void            Server::removeClient(int fd){
    MultiClientHandler::clearFd(fd);
    _mClients[fd-4] = NULL;
    close(fd);
}

void            Server::handleData(int fd){
    size_t          len;
    char            buffer[256];

    // if ((len = receiveData(fd-4, buffer)) > 0){ --> causes for problem need to check
    if ((len = _mClients[fd-4]->receive(buffer, sizeof(buffer))) > 0){
        buffer[len] = '\0';
        std::cout << "received: " << buffer << std::endl;
        sendData(fd-4, buffer, len);
    }
    else
        removeClient(fd);
}

void            Server::sendData(int fd, char *buffer, size_t len){
    _mClients[fd]->send(buffer, len);
}

// size_t          Server::receiveData(int fd, char *buffer){
//     return _mClients[fd]->receive(buffer, sizeof(buffer));
// }

bool            Server::isClientConnecting(int fd){
    return fd == _mAcceptor.getListenSd();
}