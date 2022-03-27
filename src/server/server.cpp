#include "server.hpp"

server::server(int port, std::string ip) : TcpAcceptor(port, ip){}

server::~server(){}

void    server::zeroFd(fd_set *set){
    FD_ZERO(set);
}

void    server::setFd(int fd, fd_set *set){
    FD_SET(fd, set);
}

void    server::clearFd(int fd, fd_set *set){
    FD_CLR(fd, set);
}

bool    server::issetFd(int fd, fd_set *set){
    return FD_ISSET(fd, set);
}