#ifndef TCPACCEPTOR_HPP
# define TCPACCEPTOR_HPP

#include "TcpStream.hpp"
#include <cstring>

class TcpAcceptor{
    public:
        TcpAcceptor(int port, std::string address);
        ~TcpAcceptor();

        int             start();
        TcpStream*      accept();

        //getters?

    private:
        int             _mLsd;
        std::string     _mAddress;
        int             _mPort;
        bool            _mListening;

    private:
        TcpAcceptor();

        void            setLsd();
        void            inetSocketAddress(struct sockaddr_in *address);
};

#endif