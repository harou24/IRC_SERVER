#include "server.hpp"

#include <sstream>

# define MAXclients_ 5

Server::Server(int port, std::string password) : _mAcceptor(port, HOST), clients_ss(), _mNbrClients(0) {
    _mIsRunning = false;
    _mPassword = password;
}

Server::~Server(){
    std::map<int, TcpStream*>::iterator it = clients_ss.begin();
    while (it != clients_ss.end())
    {
        delete it->second;
        it++;
    }
    clients_ss.clear();
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

                    if (isClientConnecting(fd) && _mNbrClients == MAXclients_)
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
            catch(std::exception &e){
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
    if (_mNbrClients == MAXclients_){
        print("ERROR", "no space left for another client....");
        return;
    }
    TcpStream *newStream = _mAcceptor.accept();
    MultiClientHandler::addFdToSet(newStream->getSd());
    clients_ss.insert(std::make_pair(newStream->getSd(), newStream));
    _mNbrClients++;
}

void            Server::removeClient(int fd){
    disconnect(fd);
    delete clients_ss.at(fd);
    clients_ss.erase(fd);
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
    std::map<int, TcpStream *>::iterator it = clients_ss.find(fd);
    if (it != clients_ss.end())
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
    if (clients_ss[fd])
        clients_ss[fd]->send(buffer, len);
}

std::string          Server::receiveData(int fd)
{
    if (!clients_ss[fd])
        return std::string("");

    char    buffer[512];
    size_t len = clients_ss[fd]->receive(buffer, 512);
    buffer[len] = '\0';
    return std::string(buffer);
}

bool            Server::isClientConnecting(int fd){
    return fd == _mAcceptor.getListenSd();
}

const std::map<int, TcpStream*>&     Server::getClients() const{
    return clients_ss;
}

std::queue<Message *>&     Server::getQueue(){
    return _mQueue;
}

std::string Server::getPassword(void) const { return _mPassword; }

void Server::disconnect(int fd)
{
    close(fd);
    MultiClientHandler::clearFd(fd);
}

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