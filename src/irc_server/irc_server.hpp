#ifndef IRC_SERVER_HPP
# define IRC_SERVER_HPP

#include <vector>
#include "server.hpp"
#include "client.hpp"

class Client;

class IrcServer {

    public:
        IrcServer(int port, std::string password);
        ~IrcServer();

        void    start(void);
        void    stop(void);

        bool    isNickInUse(const std::string &nickname);
        Client* getClientByStream(TcpStream *stream);
        Client* getClientByName(std::string name);

        void    addClient(Client* cl);
        void    removeClient(Client *cl);

        bool    isRunning(void) const;
        
    private:
        Server                  *_mServer;
        int                     _mNbclients;
        std::vector<Client *>    _clients;
    
        IrcServer();
};

#endif

