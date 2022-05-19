#include "tcp_stream.hpp"
#include <iostream>
#include <fcntl.h>

TcpStream::TcpStream(){}

TcpStream::TcpStream(int sd, struct sockaddr_in* address)
{
    peerIP_ = inet_ntoa(address->sin_addr);//converts host address in byte order to string
    peerPort_ = ntohs(address->sin_port);//converst network byte order to host byte order
    sd_ = sd; 
    fcntl(sd_, F_SETFL, O_NONBLOCK);
}

TcpStream::TcpStream(const TcpStream& src)
{
    peerPort_ = src.getPeerPort();
    peerIP_ = src.getPeerIP();
    sd_ = src.sd_;
    fcntl(sd_, F_SETFL, O_NONBLOCK);
}

TcpStream&      TcpStream::operator=(const TcpStream& src)
{
    peerPort_ = src.getPeerPort();
    peerIP_ = src.getPeerIP();
    sd_ = src.sd_;
    return *this;
}

TcpStream::~TcpStream()
{
    close(sd_);
}

ssize_t         TcpStream::send(std::string buffer, size_t len)
{
    return write(getSd(), buffer.c_str(), len);
}

ssize_t         TcpStream::receive(char *buffer, size_t len)
{
    return read(getSd(), buffer, len - 1);
}

std::string     TcpStream::getPeerIP()const {return peerIP_;}

int             TcpStream::getPeerPort()const {return peerPort_;}

int             TcpStream::getSd()const {return sd_;}

std::ostream&       operator<<(std::ostream& o , TcpStream const & src)
{
    o << "IP = " << src.getPeerIP() << std::endl;
    o << "Port = " << src.getPeerPort() << std::endl;
    o << "FD = " << src.getSd();

    return o;
}

bool    TcpStream::operator==(TcpStream& rhs)
{
    if (rhs.sd_ == this->sd_ && rhs.peerPort_ == this->peerPort_ && rhs.peerIP_ == this->peerIP_)
        return true;
    return false;
}
bool    TcpStream::operator!=(TcpStream& rhs)
{
    return !(rhs == *this);
}