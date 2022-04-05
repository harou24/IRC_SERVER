#include "Server.hpp"

Server::Server(int port, std::string password) : _mAcceptor(port, HOST), _mClients(), _mNbrClients(0) {
    _mIsRunning = true;
    _mPassword = password;
}

Server::~Server(){
    _mClients.clear();
}

void            Server::start(){
    // if (!_mIsRunning){
        _mAcceptor.init();
        MultiClientHandler::addFdToSet(_mAcceptor.getListenSd());
        // _mIsRunning = true;
    // }
    
    if(_mIsRunning){
        // std::cout << *this << std::endl;
        for (size_t i = 3; i <= MultiClientHandler::getFdmax(); i++){
            try{
                if (MultiClientHandler::isFdReadyToCommunicate(i)){
                    if (isClientConnecting(i))
                        addClient();
                    else
                        handleData(i);
                }
            }
            catch(std::exception &e){
                std::cout << e.what() << std::endl;
                std::cout << std::strerror(errno) << std::endl;
                exit(1);
            }
        }
    }
}

void            Server::stop(){
    _mIsRunning = false;
    exit(1);
}

void            Server::addClient(){
    if (_mNbrClients == MAX_CLIENTS){
        std::cout << "no space left for another client....\n";
        return;
    }
    TcpStream *newStream = _mAcceptor.accept();
    MultiClientHandler::addFdToSet(newStream->getSd());
    _mClients.insert(std::make_pair(newStream->getSd(), newStream));
    // _mClients[newStream->getSd() - FD_CORRECTION] = newStream;
    _mNbrClients++;

    size_t          len;
    char            buffer[512];

    std::cout << newStream->getSd() << std::endl;
    if ((len = receiveData(newStream->getSd(), buffer, sizeof(buffer))) > 0){
        buffer[len] = '\0';
        _mQueue.push(createMessage(buffer, newStream->getSd()));
    }
}

void            Server::removeClient(int fd){
    MultiClientHandler::clearFd(fd);
    _mClients.erase(fd);
    // _mClients[fd - FD_CORRECTION] = NULL;
    close(fd);
    _mNbrClients--;
}

void            Server::handleData(int fd){
    size_t          len;
    char            buffer[512];

    if ((len = receiveData(fd, buffer, sizeof(buffer))) > 0){
        buffer[len] = '\0';
        _mQueue.push(createMessage(buffer, fd));
        // sendData(fd - FD_CORRECTION, buffer, len);
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

const std::map<int, TcpStream*>&     Server::getClients() const{
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
int                     Server::getNbrClients() const{
    return _mNbrClients;
}

std::ostream&   operator<<(std::ostream& o, Server const& src){
    // size_t s = 0;
    // for (int i = 0; i < MAX_CLIENTS; i++){
    //     if (src.getClients()[i] != NULL){
    //         o << *(src.getClients()[i]) << std::endl;
    //         s++;
    //     }
    // }
    // o << "nbr clients = " << s << std::endl;
    o << "nbr " << src.getNbrClients() << std::endl;
    return o;
}