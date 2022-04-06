#ifndef TCPSTREAM_HPP
# define TCPSTREAM_HPP

#include <sys/socket.h>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

class TcpStream
{
    private:
        int             _mSd;
        std::string     _mPeerIP;
        int             _mPeerPort;

    public:
        TcpStream();
        TcpStream(int sd, struct sockaddr_in* address);
        TcpStream(const TcpStream& src);
        ~TcpStream();

        ssize_t         send(std::string buffer, size_t len);
        ssize_t         receive(char* buffer, size_t len);

        std::string     getPeerIP() const;
        int             getPeerPort() const;
        int             getSd() const;

        TcpStream&      operator = (const TcpStream& src);

};

std::ostream&       operator << (std::ostream& o , TcpStream const & src);

#endif