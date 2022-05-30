#ifndef TCPACCEPTOR_HPP
# define TCPACCEPTOR_HPP

#include "tcp_stream.hpp"

#include <cstring>
#include <stdexcept>
#include <iostream>
#include <cerrno>

class TcpAcceptor{
    public:
        TcpAcceptor(int port, std::string address);
        ~TcpAcceptor();

        int             init();
        TcpStream*      accept();
        int             getListenSd() const;

    private:
        TcpAcceptor();

        void            createListenSocket();
        int             bindSocket(struct sockaddr_in *address);
        void            inetSocketAddress(struct sockaddr_in *address);
        int             setSocketListen();
        void            setSocketOptions();

    private:
        int             listenSd_;
        std::string     address_;
        int             port_;
        bool            listening_;
};

std::ostream&           operator<<(std::ostream& o, TcpAcceptor const& src);

#endif