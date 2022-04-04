#ifndef TCPACCEPTOR_HPP
# define TCPACCEPTOR_HPP

#include "TcpStream.hpp"
#include <cstring>
#include <stdexcept>
#include <iostream>

class TcpAcceptor{
    public:
        TcpAcceptor(int port, std::string address);
        ~TcpAcceptor();

        void            init();
        TcpStream*      accept();
        int             getListenSd() const;
        int             getPort() const;
        std::string     getAddress() const;
        bool            isListening() const;

    private:
        int             _mListenSd;
        std::string     _mAddress;
        int             _mPort;
        bool            _mListening;

    private:
        TcpAcceptor();

        void            createListenSocket();
        void            bindSocket(struct sockaddr_in *address);
        void            inetSocketAddress(struct sockaddr_in *address);
        void            setSocketListen();
        void            setSocketOptions();
};

std::ostream&           operator<<(std::ostream& o, TcpAcceptor const& src);

#endif