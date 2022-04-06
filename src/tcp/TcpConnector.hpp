#ifndef TCPCONNECTOR_HPP
# define TCPCONNECTOR_HPP

#include "TcpStream.hpp"
#include <netdb.h>
#include <cstring>
#include <stdexcept>
#include <cerrno>

class TcpConnector{
    public:
        TcpStream*      connect(int port, std::string server);

    private:
        int             resolveHost(std::string host, struct in_addr* addr);

};

#endif