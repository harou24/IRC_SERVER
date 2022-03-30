#ifndef SERVER_HPP
# define SERVER_HPP

# include "MultiClientHandler.hpp"
# include "TcpAcceptor.hpp"
# include "TcpStream.hpp"

# include <vector>
# include <iostream>

# define MAX_CLIENTS 5
# define HOST "127.0.0.1"
# define FD_CORRECTION 4

class Server : public MultiClientHandler
{
    private:
        TcpAcceptor                 _mAcceptor;
        std::vector<TcpStream*>     _mClients;
        bool                        _mIsRunning;
        std::string                 _mPassword;

        Server(void);

    public:
        Server(int port, std::string password);
        ~Server(void);

        void start(void);
        void stop(void);

        void addClient(void);
        void removeClient(int fd);

        void handleData(int fd);
        void sendData(int fd, char *buffer, size_t len);
        size_t receiveData(int fd, char *buffer, size_t len);

        bool isClientConnecting(int fd);

};

#endif
