#ifndef TCPSTREAM_HPP
# define TCPSTREAM_HPP

#include <sys/socket.h>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>

// class TcpConnector;s

class TcpStream
{
    public:
        ~TcpStream();

        ssize_t         send(std::string buffer, size_t len);
        ssize_t         receive(std::string buffer, size_t len);

        std::string     getPeerIP() const;
        int             getPeerPort() const;
        int             getSd() const;

    private:
        int             _mSd;
        std::string     _mPeerIP;
        int             _mPeerPort;

    public:
        TcpStream();
        TcpStream(int sd, struct sockaddr_in* address);
        TcpStream(const TcpStream& src);

};

#endif