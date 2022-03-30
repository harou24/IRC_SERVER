#include "TcpStream.hpp"
#include <iostream>
TcpStream::TcpStream(){}

TcpStream::TcpStream(int sd, struct sockaddr_in* address){
    _mPeerIP = inet_ntoa(address->sin_addr);//converts host address in byte order to string
    _mPeerPort = ntohs(address->sin_port);//converst network byte order to host byte order
    _mSd = sd; 
}

TcpStream::TcpStream(const TcpStream& src){
    _mPeerPort = src.getPeerPort();
    _mPeerIP = src.getPeerIP();
    _mSd = src._mSd;
}

TcpStream::~TcpStream(){
    close(_mSd);
}

ssize_t         TcpStream::send(std::string buffer, size_t len){
    return write(getSd(), buffer.c_str(), len);
}

ssize_t         TcpStream::receive(char *buffer, size_t len){
    return read(getSd(), buffer, len);
}

std::string     TcpStream::getPeerIP()const {return _mPeerIP;}

int             TcpStream::getPeerPort()const {return _mPeerPort;}

int             TcpStream::getSd()const {return _mSd;}

std::ostream&       operator<<(std::ostream& o , TcpStream const & src){
    o << "IP = " << src.getPeerIP() << std::endl;
    o << "Port = " << src.getPeerPort() << std::endl;
    o << "FD = " << src.getSd();

    return o;
}
