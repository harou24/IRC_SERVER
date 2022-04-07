#include "IrcServer.hpp"

#define RPL_WELCOME(nick, args) ":" + args.arg3 + " 001 " + nick + "\n: Welcome to the Internet Relay Network\n" + nick + "!" + args.arg1 + "@" + args.arg2 + "\n"
#define RPL_YOURHOST(args) ":Your host is " + args.arg3 + ", running version 1.0\n"
#define RPL_CREATED ":This server was created 12.54.22 Apr 06 2022\n"
#define LOGOO "          _          _            _                     \n \
        /\\ \\       /\\ \\        /\\ \\     \n\
         \\ \\ \\     /  \\ \\      /  \\ \\    \n\
         /\\ \\_\\   / /\\ \\ \\    / /\\ \\ \\   \n\
        / /\\/_/  / / /\\ \\_\\  / / /\\ \\ \\  \n\
       / / /    / / /_/ / / / / /  \\ \\_\\ \n\
      / / /    / / /__\\/ / / / /    \\/_/ \n\
     / / /    / / /_____/ / / /          \n\
 ___/ / /__  / / /\\ \\ \\  / / /________  \n\
/\\__\\/_/___\\/ / /  \\ \\ \\/ / /_________\\  \n\
\\/_________/\\/_/    \\_\\/\\/____________/   \n\n"
#define LOGO "                            _ _  \n \
       //||\\\\   ///||\\   /.-. | \n\
        ` @ @\\     a a   ||o_o|| \n\
           >        _)   || = || \n\
           -        ~      ' '   \n\
       haroutioun eutienne evita\n\n "

#define PING(str) ":" + str + " PONG " + str + " :" + str + "\n"
#define PING1(str) "PING :" + str
#define RPL_AWAY(nick, message) nick + " :" + message + "\n"
#define RPL_UNAWAY() ": You are no longer marked as being away\n"
#define RPL_NOAWAY() ": You have been marked as being away\n"
#define PRIV_MESSAGE(nick, nick2, host, message) ":" + nick + "!" + nick + "@" + host + "\n PRIVMSG " + nick2 + " " + message + "\n"
#define RPL_UMODEIS(host, args) ":" + args.arg1 + "!" + args.arg1 + "@" + host + " MODE " + args.arg1 + " :" + args.arg2 +  "\n"
#define RPL_NICK(server, user, nick) ":" + user + "!" + user + "@" + server + " NICK :" + nick + "\n"

IrcServer::IrcServer(int port, std::string password) : _mServer(port, password) {}

IrcServer::~IrcServer() {}

void    IrcServer::processMessage()
{
    std::string s;
    void    (IrcServer::*p2f[])(const Args& args, TcpStream& stream) = {&IrcServer::away, &IrcServer::invite, \
        &IrcServer::join, &IrcServer::me, &IrcServer::msg, &IrcServer::nick, &IrcServer::notice, \
        &IrcServer::part, &IrcServer::privmsg, &IrcServer::query, &IrcServer::quit, \
        &IrcServer::whois, &IrcServer::mode, &IrcServer::user, &IrcServer::ping};
    _mServer.init();
    while (1)
    {
        _mServer.runOnce();
        while (_mServer.getQueue().size() > 0)
        {
            for (std::stringstream ss(_mServer.getQueue().front().data ); std::getline(ss, s, '\n');)
            {
                _mData.parse(s);
                std::cout << s << std::endl;
                if (_mData.getCommand() != UNKNOWN)
                    (this->*p2f[_mData.getCommand()])(_mData.getArgument(), *_mServer.getQueue().front().stream);
            }
            _mServer.getQueue().pop();
        }
    }
}

 void    IrcServer::nick(const Args& args, TcpStream& stream)
 {
    std::vector<Clients*>::iterator it;
    std::string s;
    for(it = _mClient.begin(); it != _mClient.end() && (*it)->getStream() != stream; it++) {}
    if (it != _mClient.end() && (*it)->getStream() == stream)
    {
        (*it)->setNick(args.arg1);
        s = RPL_NICK((*it)->getServer(), (*it)->getUser(), (*it)->getNick());
        stream.send(s, s.length());
    }

    else
    {
        Clients *c = new Clients(args.arg1, stream);
        _mClient.push_back(c);
    }
 }

void    IrcServer::away(const Args& args, TcpStream& stream) {
    std::vector<Clients*>::iterator it;
    for(it = _mClient.begin(); it != _mClient.end() && (*it)->getStream() != stream; it++) {}
    if (it != _mClient.end() && (*it)->getStream() == stream)
    {
		std::string s;
		if ((*it)->getAway() == false || args.arg1 == "")
		{
			s = RPL_NOAWAY();
			(*it)->setAway(true);
			(*it)->setAwayMessage(args.arg1);
    		stream.send(s, s.length());
		}
		else
		{
			s = RPL_UNAWAY();
			(*it)->setAway(false);
			(*it)->setAwayMessage("");	
    		stream.send(s, s.length());
		}
	}
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
    if (it != _mClient.end() && (*it)->getStream() == stream){
		for (std::vector<Clients*>::iterator it2 = _mClient.begin(); it2 != _mClient.end(); it2++)
		{
			if ((*it2)->getNick() == args.arg1)
			{
				std::string s = PRIV_MESSAGE((*it)->getNick(), args.arg1, (*it)->getHost(), args.arg2);
    			(*it2)->getStream().send(s, s.length());
				break ;
			}
		}
    

	}
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
    {
        std::string s = RPL_UMODEIS((*it)->getServer(), args);
        stream.send(s, s.length());
    }
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
    std::string s = "blablablabl\n";
    s = PING1(s);
    stream.send(s, s.length());
    s = "CAP * LS :away-notify\n";
    stream.send(s, s.length());
    sleep(1);
    // s = "CAP * ACK :multi-prefix sasl";
    // stream.send(s, s.length());
    s = RPL_WELCOME(it->getNick(), args);
    stream.send(s, s.length());
    s = RPL_YOURHOST(args);
    stream.send(s, s.length());
    s = RPL_CREATED;
    stream.send(s, s.length());
    s = LOGOO;
    stream.send(s, s.length());
    s = LOGO;
    stream.send(s, s.length());

    // s = RPL_MYINFO((*it)->getNick(), args);
    // stream.send(s, s.length());
}
