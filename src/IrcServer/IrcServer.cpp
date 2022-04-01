#include "IrcServer.hpp"

IrcServer::IrcServer(int port, std::string password) : _mServer(port, password) {}

IrcServer::~IrcServer() {}

// void    startServer(int port, std::string password);
void    IrcServer::processMessage()
{
    std::string s;
    void    (IrcServer::*p2f[])(const Args& args, TcpStream& stream) = {&IrcServer::away, &IrcServer::invite, \
        &IrcServer::join, &IrcServer::me, &IrcServer::msg, &IrcServer::nick, &IrcServer::notice, \
        &IrcServer::part, &IrcServer::privmsg, &IrcServer::query, &IrcServer::quit, \
        &IrcServer::whois, &IrcServer::mode, &IrcServer::user, &IrcServer::ping};
    while (1)
    {
        _mServer.start();
        while (_mServer.getQueue().size() > 0)
        {
            for (std::stringstream ss(_mServer.getQueue().front().data ); std::getline(ss, s, '\n');)
            {
                _mData.parse(s);
                if (_mData.getCommand() != UNKNOWN)
                    (this->*p2f[_mData.getCommand()])(_mData.getArgument(), *_mServer.getQueue().front().stream);
                std::cout << s << std::endl;
                std::cout << _mData.getRaw() << std::endl;
            }
            _mServer.getQueue().pop();
        }
    }
}

 void    IrcServer::nick(const Args& args, TcpStream& stream)
 {
     std::vector<Clients>::iterator it;
     for(it = _mClient.begin(); it != _mClient.end() && it->getStream() != stream; it++) {}
     if (it != _mClient.end())
        it->setNick(args.arg1);
 }

void    IrcServer::away(const Args& args, TcpStream& stream) {
    std::vector<Clients>::iterator it;
     for(it = _mClient.begin(); it != _mClient.end() && it->getStream() != stream; it++) {}
     if (it != _mClient.end())
        it->setNick(args.arg1);
}
void    IrcServer::invite(const Args& args, TcpStream& stream){
    std::vector<Clients>::iterator it;
     for(it = _mClient.begin(); it != _mClient.end() && it->getStream() != stream; it++) {}
     if (it != _mClient.end())
        it->setNick(args.arg1);
}
void    IrcServer::join(const Args& args, TcpStream& stream){
    std::vector<Clients>::iterator it;
     for(it = _mClient.begin(); it != _mClient.end() && it->getStream() != stream; it++) {}
     if (it != _mClient.end())
        it->setNick(args.arg1);
}
void    IrcServer::me(const Args& args, TcpStream& stream){
    std::vector<Clients>::iterator it;
     for(it = _mClient.begin(); it != _mClient.end() && it->getStream() != stream; it++) {}
     if (it != _mClient.end())
        it->setNick(args.arg1);
}
void    IrcServer::msg(const Args& args, TcpStream& stream){
    std::vector<Clients>::iterator it;
     for(it = _mClient.begin(); it != _mClient.end() && it->getStream() != stream; it++) {}
     if (it != _mClient.end())
        it->setNick(args.arg1);
}
void    IrcServer::notice(const Args& args, TcpStream& stream){
    std::vector<Clients>::iterator it;
     for(it = _mClient.begin(); it != _mClient.end() && it->getStream() != stream; it++) {}
     if (it != _mClient.end())
        it->setNick(args.arg1);
}
void    IrcServer::part(const Args& args, TcpStream& stream){
    std::vector<Clients>::iterator it;
     for(it = _mClient.begin(); it != _mClient.end() && it->getStream() != stream; it++) {}
     if (it != _mClient.end())
        it->setNick(args.arg1);
}
void    IrcServer::privmsg(const Args& args, TcpStream& stream){
    std::vector<Clients>::iterator it;
     for(it = _mClient.begin(); it != _mClient.end() && it->getStream() != stream; it++) {}
     if (it != _mClient.end())
        it->setNick(args.arg1);
}
void    IrcServer::query(const Args& args, TcpStream& stream){
    std::vector<Clients>::iterator it;
     for(it = _mClient.begin(); it != _mClient.end() && it->getStream() != stream; it++) {}
     if (it != _mClient.end())
        it->setNick(args.arg1);
}
void    IrcServer::quit(const Args& args, TcpStream& stream){
    std::vector<Clients>::iterator it;
     for(it = _mClient.begin(); it != _mClient.end() && it->getStream() != stream; it++) {}
     if (it != _mClient.end())
        it->setNick(args.arg1);
}
void    IrcServer::whois(const Args& args, TcpStream& stream){
    std::vector<Clients>::iterator it;
     for(it = _mClient.begin(); it != _mClient.end() && it->getStream() != stream; it++) {}
     if (it != _mClient.end())
        it->setNick(args.arg1);
}
void    IrcServer::mode(const Args& args, TcpStream& stream){
    std::vector<Clients>::iterator it;
     for(it = _mClient.begin(); it != _mClient.end() && it->getStream() != stream; it++) {}
     if (it != _mClient.end())
        it->setNick(args.arg1);
}
void    IrcServer::user(const Args& args, TcpStream& stream){
    std::vector<Clients>::iterator it;
     for(it = _mClient.begin(); it != _mClient.end() && it->getStream() != stream; it++) {}
     if (it != _mClient.end())
        it->setNick(args.arg1);
}
void    IrcServer::ping(const Args& args, TcpStream& stream){
    std::vector<Clients>::iterator it;
     for(it = _mClient.begin(); it != _mClient.end() && it->getStream() != stream; it++) {}
     if (it != _mClient.end())
        it->setNick(args.arg1);
}