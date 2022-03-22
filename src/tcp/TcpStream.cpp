#include "TcpStream.hpp"
#include <arpa/inet.h>

TcpStream::TcpStream(){}

TcpStream::TcpStream(int sd, struct sockaddr_in* address){
    char    dst[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, (struct in_addr*)(address->sin_addr.s_addr), dst, INET_ADDRSTRLEN);
    _mPeerIP = dst;

}

TcpStream::TcpStream(const TcpStream& src){}

TcpStream::~TcpStream(){}

std::string     TcpStream::getPeerIP(){return _mPeerIP;}

int             TcpStream::getPeerPort(){return _mPeerPort;}

