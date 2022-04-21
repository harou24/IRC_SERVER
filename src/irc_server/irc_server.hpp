#ifndef IRC_SERVER_HPP
# define IRC_SERVER_HPP

#include <vector>
#include "server.hpp"
#include "client.hpp"


class IrcServer{
    public:
        IrcServer(int port, std::string password);
        ~IrcServer();

        void    start(void);

    private:
        Server                  _mServer;
        int                     _mNbclients;
        std::vector<Client *>    _mClient;
    
        IrcServer();
};

#endif

