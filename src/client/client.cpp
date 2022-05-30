#include "client.hpp"

Client::Client(const std::string& nick, TcpStream* stream) : nickname_(nick), username_(""), hostname_(""), 
servername_(""), realname_(""), stream_(stream), away_(false), awayMsg_(""), passwordUsedToConnect_("")
{
}

Client::Client(const Client& src) 
: nickname_(src.getNick()), username_(src.getUser()), hostname_(src.getHost()),
servername_(src.getServer()), realname_(src.getReal()), stream_(src.stream_)
{
}

Client::~Client()
{
}

void            Client::setNick(const std::string& s) {nickname_ = s;}
void            Client::setPasswordUsedToConnect(const std::string& s) {passwordUsedToConnect_ = s;}
void            Client::setUser(const std::string& s) {username_ = s;}
void            Client::setHost(const std::string& s) {hostname_ = s;}
void            Client::setServer(const std::string& s) {servername_ = s;}
void            Client::setReal(const std::string& s) {realname_ = s;}
void            Client::setAwayMsg(std::string msg) {awayMsg_ = msg;}
void            Client::setAway(bool status) {away_ = status;}

std::string     Client::getNick() const {return nickname_;}
std::string     Client::getUser() const {return username_;}
std::string     Client::getHost() const {return hostname_;}
std::string     Client::getServer() const {return servername_;}
std::string     Client::getReal() const {return realname_;}
TcpStream&      Client::getStream() const {return *stream_;}
bool            Client::getAway() const {return away_;}
std::string     Client::getAwayMsg() const {return awayMsg_;}
std::string     Client::getPasswordUsedToConnect() const {return passwordUsedToConnect_;}

std::ostream&   operator<<(std::ostream& o, const Client & src)
{
    o << "Nick = " << src.getNick() << std::endl;
    o << "User = " << src.getUser() << std::endl;
    o << "Host = " << src.getHost() << std::endl;
    o << "Server = " << src.getServer() << std::endl;
    o << "Real = " << src.getReal() << std::endl;
    return o;
}
