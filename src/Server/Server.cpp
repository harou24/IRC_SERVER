#include "Server.hpp"

Server::Server(int port, std::string password) : _mAcceptor(port, HOST), _mClients(), _mNbrClients(0) {
    _mIsRunning = false;
    _mPassword = password;
}

Server::~Server(){
    
    std::map<int, TcpStream*>::iterator it = _mClients.begin();
    while (it != _mClients.end())
    {
        delete it->second;
        it++;
    }
    _mClients.clear();
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
                std::cout << e.what() << std::endl;
                exit(1);
            }
        }
    }
}

void            Server::stop(){
    _mIsRunning = false;
}

void            Server::addClient(){
    if (_mNbrClients == MAX_CLIENTS){
        std::cout << "no space left for another client....\n";
        return;
    }
    TcpStream *newStream = _mAcceptor.accept();
    MultiClientHandler::addFdToSet(newStream->getSd());
    _mClients.insert(std::make_pair(newStream->getSd(), newStream));
    _mNbrClients++;
}

void            Server::removeClient(int fd){
    MultiClientHandler::clearFd(fd);
    _mClients.erase(fd);
    close(fd);
    _mNbrClients--;
}

void            Server::handleData(int fd){
    size_t          len;
    char            buffer[512];

    if ((len = receiveData(fd, buffer, sizeof(buffer))) > 0){
        buffer[len] = '\0';
        _mQueue.push(createMessage(buffer, fd));
    }
    else
        removeClient(fd);
}

void            Server::sendData(int fd, char *buffer, size_t len){
    if (_mClients[fd])
        _mClients[fd]->send(buffer, len);
}

size_t          Server::receiveData(int fd, char *buffer, size_t len){
    if (_mClients[fd])
        return _mClients[fd]->receive(buffer, len);
    return 0;
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
    for (std::map<int, TcpStream*>::const_iterator it = src.getClients().begin(); it != src.getClients().end(); it++)
        o << it->second << std::endl;
    o << "nbr " << src.getNbrClients() << std::endl;
    return o;
}