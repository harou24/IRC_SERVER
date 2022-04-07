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

        void    processMessage();

    private:
        Server                  _mServer;
        Parser                  _mData;
        int                     _mNbclients;
        std::vector<Clients*>    _mClient;

    private:
        IrcServer();

        void    makeClient(std::string s, const TcpStream & ts);
        void    splitStrings(std::string str);

        void    away(const Args& args, TcpStream& stream);
        void    invite(const Args& args, TcpStream& stream);
        void    join(const Args& args, TcpStream& stream);
        void    me(const Args& args, TcpStream& stream);
        void    msg(const Args& args, TcpStream& stream);
        void    nick(const Args& args, TcpStream& stream);
        void    notice(const Args& args, TcpStream& stream);
        void    part(const Args& args, TcpStream& stream);
        void    privmsg(const Args& args, TcpStream& stream);
        void    query(const Args& args, TcpStream& stream);
        void    quit(const Args& args, TcpStream& stream);
        void    whois(const Args& args, TcpStream& stream);
        void    mode(const Args& args, TcpStream& stream);
        void    user(const Args& args, TcpStream& stream);
        void    ping(const Args& args, TcpStream& stream);

        void    welcome(const Args& args, TcpStream& stream, Clients* it);
};

#endif

