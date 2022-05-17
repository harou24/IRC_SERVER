#include "client.hpp"

Client::Client(const std::string& nick, TcpStream* stream) : _mNickName(nick), _mUserName(""), _mHostName(""), 
_mServerName(""), _mRealName(""), _mStream(stream), _mAway(false), _mAwayMsg(""), _passwordUsedToConnect("")
{
}

Client::Client(const Client& src) 
: _mNickName(src.getNick()), _mUserName(src.getUser()), _mHostName(src.getHost()),
_mServerName(src.getServer()), _mRealName(src.getReal()), _mStream(src._mStream)
{
}



Client::~Client()
{
}


void            Client::setNick(const std::string& s) {_mNickName = s;}
void            Client::setPasswordUsedToConnect(const std::string& s) {_passwordUsedToConnect = s;}
void            Client::setUser(const std::string& s) {_mUserName = s;}
void            Client::setHost(const std::string& s) {_mHostName = s;}
void            Client::setServer(const std::string& s) {_mServerName = s;}
void            Client::setReal(const std::string& s) {_mRealName = s;}
void            Client::setAwayMsg(std::string msg) {_mAwayMsg = msg;}
void            Client::setAway(bool status) {_mAway = status;}

std::string     Client::getNick() const {return _mNickName;}
std::string     Client::getUser() const {return _mUserName;}
std::string     Client::getHost() const {return _mHostName;}
std::string     Client::getServer() const {return _mServerName;}
std::string     Client::getReal() const {return _mRealName;}
TcpStream&      Client::getStream() const {return *_mStream;}
bool            Client::getAway() const {return _mAway;}
std::string     Client::getAwayMsg() const {return _mAwayMsg;}
std::string     Client::getPasswordUsedToConnect() const {return _passwordUsedToConnect;}

std::ostream&   operator<<(std::ostream& o, const Client & src)
{
    o << "Nick = " << src.getNick() << std::endl;
    o << "User = " << src.getUser() << std::endl;
    o << "Host = " << src.getHost() << std::endl;
    o << "Server = " << src.getServer() << std::endl;
    o << "Real = " << src.getReal() << std::endl;
    return o;
}
