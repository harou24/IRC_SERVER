#ifndef SERVER_HPP
# define SERVER_HPP

# include "multi_client_handler.hpp"
# include "tcp_acceptor.hpp"
# include "tcp_stream.hpp"

# include <map>
# include <iostream>
# include <sys/select.h>
# include <cstdlib>
# include <queue>
# include <cerrno>

# define MAX_CLIENTS 5
# define HOST "127.0.0.1"
# define FD_CORRECTION 4

struct Message
{
    std::string     data;
    TcpStream       *stream;
};

class Server : public MultiClientHandler
{
    private:
        TcpAcceptor                 _mAcceptor;
        std::map<int, TcpStream*>   _mClientss;
        int                         _mNbrClients;
        bool                        _mIsRunning;
        std::string                 _mPassword;
        std::queue<Message>         _mQueue;

        Server(void);
        
        Message createMessage(std::string str, int fd);

    public:
        Server(int port, std::string password);
        ~Server(void);

        void runOnce(void);
        void init(void);
        void start(void);
        void stop(void);

        void addClient(void);
        void removeClient(int fd);

        void handleData(int fd);
        void sendData(int fd, char *buffer, size_t len);
        size_t receiveData(int fd, char *buffer, size_t len);

        bool isClientConnecting(int fd);

        const std::map<int, TcpStream*>&      getClients() const;

        std::queue<Message>&                 getQueue();

        std::string getPassword(void) const;
        bool isRunning(void) const;
        int                                 getNbrClients() const;

        Message getNextMsg(void);
};

std::ostream&   operator<<(std::ostream& o, Server const& src);

#endif
