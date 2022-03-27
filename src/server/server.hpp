#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/select.h>
#include "../tcp/TcpAcceptor.hpp"

class server : public TcpAcceptor{
    public:
        server(int port, std::string ip);
        ~server();

        void    zeroFd(fd_set *set);
        void    setFd(int fd, fd_set *set);
        void    clearFd(int fd, fd_set *set);
        bool    issetFd(int fd, fd_set *set);

        

    private:
        // fd_set      _mMasterFds;
        // fd_set      _mReadFds;
        // int         _mMax;
};

#endif