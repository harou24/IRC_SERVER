#ifndef TCPSTREAM_HPP
# define TCPSTREAM_HPP

#include <sys/socket.h>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

class TcpStream
{
    public:
        ~TcpStream();

        ssize_t         send(std::string buffer, size_t len);
        ssize_t         receive(char* buffer, size_t len);

        std::string     getPeerIP() const;
        int             getPeerPort() const;
        int             getSd() const;
        unsigned int    getTimeStamp() const;
        std::string     getPing() const;
        std::string     getBuffer() const;

        void            setTimeStamp(unsigned int time);
        void            setPing(std::string str);
        void            addToBuffer(std::string str);

        void            emptyBuffer();

        bool    operator==(TcpStream& rhs);
        bool    operator!=(TcpStream& rhs);


    public:
        TcpStream();
        TcpStream(int sd, struct sockaddr_in* address);
        TcpStream(const TcpStream& src);

        TcpStream&      operator=(const TcpStream& src);

    private:
        int             sd_;
        std::string     peerIP_;
        int             peerPort_;
        unsigned int    timeStamp_;
        std::string     ping_;
        std::string     buffer_;
};

std::ostream&       operator<<(std::ostream& o , TcpStream const & src);

#endif