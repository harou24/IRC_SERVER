#ifndef SERVER_HPP
# define SERVER_HPP

# include "MultiClientHandler.hpp"
# include "TcpAcceptor.hpp"
# include "TcpStream.hpp"

# include <vector>

# define MAX_CLIENTS 5

class Server: public MultiClientHandler
{
    private:
        TcpAcceptor acceptor;
        std::vector<TcpStream*>  clients;
        bool    isRunning;

    public:
        Server(void);
        Server(int port, std::string password);
        ~Server(void);

        void start(void);
        void stop(void);
        void stopSigHandler(int pid);

        void addClient(void);
        void removeClient(void);

        void handleData(void);
        void sendData(int fd);
        void receiveData(int fd);

        bool isClientConnecting(int fd);

};

#endif
