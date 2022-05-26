#ifndef SERVER_HPP
# define SERVER_HPP

# include "multi_client_handler.hpp"
# include "tcp_acceptor.hpp"
# include "tcp_stream.hpp"
# include "message.hpp"
# include "print.hpp"
# include "colors.h"

# include <map>
# include <iostream>
# include <sys/select.h>
# include <cstdlib>
# include <queue>
# include <cerrno>

# define HOST "127.0.0.1"

class Server : public MultiClientHandler
{
    public:
        Server(int port, std::string password, std::string host);
        ~Server(void);

        void runOnce(void);
        void init(void);
        void start(void);
        void stop(void);

        std::queue<std::string> split(const std::string &data);

        void addClient(void);
        void removeClient(int fd);

        void handleData(int fd);
        void sendData(int fd, char *buffer, size_t len);
        std::string receiveData(int fd);

        bool isClientConnecting(int fd);

        const std::map<int, TcpStream*>&      getClients() const;

        std::queue<Message *>&                 getQueue();

        std::string getPassword(void) const;
        bool isRunning(void) const;
        int                                 getNbrClients() const;

        Message& getNextMsg(void);
        TcpStream *getStreamFromFd(int fd);

        void    disconnect(int fd);
    
    private:
        TcpAcceptor                 acceptor_;
        std::map<int, TcpStream*>   clients_ss_;
        int                         nbrClients_;
        bool                        isRunning_;
        std::string                 password_;
        std::queue<Message*>        queue_;

        Server(void);
};

std::ostream&   operator<<(std::ostream& o, Server const& src);

#endif
