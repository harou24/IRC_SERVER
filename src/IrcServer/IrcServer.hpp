#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

#include "Server.hpp"

class IrcServer{
    public:
        IrcServer(int port, std::string password);
        ~IrcServer();



    private:
        Server          _mServer;
        Parser          _mData;
        int             _mNbclients;
        //create vector of clients ---> make client class @eu
    
    private:
        IrcServer()
};

#endif