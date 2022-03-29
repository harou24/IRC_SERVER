#ifndef SERVER_HPP
# define SERVER_HPP

# include "../MultiClientHandler/MultiClientHandler.hpp"
# include "../tcp/TcpAcceptor.hpp"
# include "../tcp/TcpStream.hpp"

# include <vector>

# define MAX_CLIENTS 5
# define HOST "127.0.0.1"

class Server: public MultiClientHandler
{
    private:
        TcpAcceptor                 acceptor;
        std::vector<TcpStream*>     clients;
        bool                        isRunning;
        std::string                 _mPassword;

        Server(void);
    public:
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
