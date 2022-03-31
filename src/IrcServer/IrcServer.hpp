#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

#include <vector>
#include "Server.hpp"
#include "parser.hpp"
#include "Clients.hpp"

class IrcServer{
    public:
        IrcServer(int port, std::string password);
        ~IrcServer();

        void    startServer(int port, std::string password);

    private:
        Server                  _mServer;
        Parser                  _mData;
        int                     _mNbclients;
        std::vector<Clients>    _Client;
        //create vector of clients ---> make client class @eu
    
    private:
        IrcServer();
};

#endif