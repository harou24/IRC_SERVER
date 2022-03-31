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

        // void    startServer(int port, std::string password);
        // void    processMessage(Message& msg);
        void    processMessage();
        // void    

    private:
        Server                  _mServer;
        Parser                  _mData;
        int                     _mNbclients;
        std::vector<Clients>    _mClient;
        //create vector of clients ---> make client class @eu
    
    private:
        IrcServer();
        
        void    makeClient(std::string s, const TcpStream & ts);
        void    splitStrings(std::string str);

        void    away(const std::string& str);
        void    invite(const std::string& str);
        void    join(const std::string& str);
        void    me(const std::string& str);
        void    msg(const std::string& str);
        void    nick(const std::string& str);
        void    notice(const std::string& str);
        void    part(const std::string& str);
        void    privmsg(const std::string& str);
        void    query(const std::string& str);
        void    quit(const std::string& str);
        void    whois(const std::string& str);
        void    mode(const std::string& str);
        void    user(const std::string& str);
        void    ping(const std::string& str);
};

#endif

// server starten  met ircserver
