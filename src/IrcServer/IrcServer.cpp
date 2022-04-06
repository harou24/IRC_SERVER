#include "IrcServer.hpp"

#define RPL_WELCOME(nick, args) ":" + args.arg3 + " 001 " + nick + "\n: Welcome to the Internet Relay Network\n" + nick + "!" + args.arg1 + "@" + args.arg2 + "\n"
#define RPL_YOURHOST(args) ":Your host is " + args.arg3 + ", running version 1.0\n"
#define RPL_CREATED ":This server was created 12.54.22 Apr 06 2022\n"
#define PING(str) ": " + str + " PONG " + str + " :" + str + "\n"

IrcServer::IrcServer(int port, std::string password) : _mServer(port, password) {}

IrcServer::~IrcServer() {}

void    IrcServer::processMessage()
{
    std::string s;
    void    (IrcServer::*p2f[])(const Args& args, TcpStream& stream) = {&IrcServer::away, &IrcServer::invite, \
        &IrcServer::join, &IrcServer::me, &IrcServer::msg, &IrcServer::nick, &IrcServer::notice, \
        &IrcServer::part, &IrcServer::privmsg, &IrcServer::query, &IrcServer::quit, \
        &IrcServer::whois, &IrcServer::mode, &IrcServer::user, &IrcServer::ping};
    _mServer.runOnce();
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
            }
            _mServer.getQueue().pop();
        }
    }
}

 void    IrcServer::nick(const Args& args, TcpStream& stream)
 {
    std::vector<Clients*>::iterator it;
    for(it = _mClient.begin(); it != _mClient.end() && (*it)->getStream() != stream; it++) {}
    if (it != _mClient.end() && (*it)->getStream() == stream)
        (*it)->setNick(args.arg1);
    else
    {
        Clients *c = new Clients(args.arg1, stream);
        _mClient.push_back(c);
    }
 }

void    IrcServer::away(const Args& args, TcpStream& stream) {
    std::vector<Clients*>::iterator it;
    for(it = _mClient.begin(); it != _mClient.end() && (*it)->getStream().getSd() != 0 && (*it)->getStream() != stream; it++) {}
    if (it != _mClient.end() && (*it)->getStream() == stream)
        (*it)->setNick(args.arg1);
}
void    IrcServer::invite(const Args& args, TcpStream& stream){
    std::vector<Clients*>::iterator it;
    for(it = _mClient.begin(); it != _mClient.end() && (*it)->getStream() != stream; it++) {}
    if (it != _mClient.end() && (*it)->getStream() == stream)
        (*it)->setNick(args.arg1);
}
void    IrcServer::join(const Args& args, TcpStream& stream){
    std::vector<Clients*>::iterator it;
    for(it = _mClient.begin(); it != _mClient.end() && (*it)->getStream() != stream; it++) {}
    if (it != _mClient.end() && (*it)->getStream() == stream)
        (*it)->setNick(args.arg1);
}
void    IrcServer::me(const Args& args, TcpStream& stream){
    std::vector<Clients*>::iterator it;
    for(it = _mClient.begin(); it != _mClient.end() && (*it)->getStream() != stream; it++) {}
    if (it != _mClient.end() && (*it)->getStream() == stream)
        (*it)->setNick(args.arg1);
}
void    IrcServer::msg(const Args& args, TcpStream& stream){
    std::vector<Clients*>::iterator it;
    for(it = _mClient.begin(); it != _mClient.end() && (*it)->getStream() != stream; it++) {}
    if (it != _mClient.end() && (*it)->getStream() == stream)
        (*it)->setNick(args.arg1);
}
void    IrcServer::notice(const Args& args, TcpStream& stream){
    std::vector<Clients*>::iterator it;
    for(it = _mClient.begin(); it != _mClient.end() && (*it)->getStream() != stream; it++) {}
    if (it != _mClient.end() && (*it)->getStream() == stream)
        (*it)->setNick(args.arg1);
}
void    IrcServer::part(const Args& args, TcpStream& stream){
    std::vector<Clients*>::iterator it;
    for(it = _mClient.begin(); it != _mClient.end() && (*it)->getStream() != stream; it++) {}
    if (it != _mClient.end() && (*it)->getStream() == stream)
        (*it)->setNick(args.arg1);
}
void    IrcServer::privmsg(const Args& args, TcpStream& stream){
    std::vector<Clients*>::iterator it;
    for(it = _mClient.begin(); it != _mClient.end() && (*it)->getStream() != stream; it++) {}
    if (it != _mClient.end() && (*it)->getStream() == stream)
        (*it)->setNick(args.arg1);
}
void    IrcServer::query(const Args& args, TcpStream& stream){
    std::vector<Clients*>::iterator it;
    for(it = _mClient.begin(); it != _mClient.end() && (*it)->getStream() != stream; it++) {}
    if (it != _mClient.end() && (*it)->getStream() == stream)
        (*it)->setNick(args.arg1);
}
void    IrcServer::quit(const Args& args, TcpStream& stream){
    std::vector<Clients*>::iterator it;
    for(it = _mClient.begin(); it != _mClient.end() && (*it)->getStream() != stream; it++) {}
    if (it != _mClient.end() && (*it)->getStream() == stream)
        (*it)->setNick(args.arg1);
}
void    IrcServer::whois(const Args& args, TcpStream& stream){
    std::vector<Clients*>::iterator it;
    for(it = _mClient.begin(); it != _mClient.end() && (*it)->getStream() != stream; it++) {}
    if (it != _mClient.end() && (*it)->getStream() == stream)
        (*it)->setNick(args.arg1);
}
void    IrcServer::mode(const Args& args, TcpStream& stream){
    std::vector<Clients*>::iterator it;
    for(it = _mClient.begin(); it != _mClient.end() && (*it)->getStream() != stream; it++) {}
    if (it != _mClient.end() && (*it)->getStream() == stream)
        (*it)->setNick(args.arg1);
}
void    IrcServer::user(const Args& args, TcpStream& stream){
    std::vector<Clients*>::iterator it;
    for(it = _mClient.begin(); it != _mClient.end() && (*it)->getStream() != stream; it++) {}
     if (it != _mClient.end()){
        (*it)->setUser(args.arg1);
        (*it)->setHost(args.arg2);
        (*it)->setServer(args.arg3);
        (*it)->setReal(args.arg4);
        if (!(*it)->getHandShake()){
            welcome(args, stream, *it);
            (*it)->setHandShake();
        }
     }
}
void    IrcServer::ping(const Args& args, TcpStream& stream){
    std::string s = PING(args.arg1);
    stream.send(s, s.length());
}
void    IrcServer::welcome(const Args& args, TcpStream& stream, Clients* it){
    std::string s;
    s = RPL_WELCOME(it->getNick(), args);
    stream.send(s, s.length());
    s = RPL_YOURHOST(args);
    stream.send(s, s.length());
    s = RPL_CREATED;
    stream.send(s, s.length());
    // s = RPL_MYINFO((*it)->getNick(), args);
    // stream.send(s, s.length());
}
