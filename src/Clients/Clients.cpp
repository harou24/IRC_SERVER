#include "Clients.hpp"

Clients::Clients(const std::string& nick, TcpStream& stream) : _mNickName(nick), _mUserName(""), _mHostName(""), 
_mServerName(""), _mRealName(""), _mAwayMessage(""), _mStream(stream), _mAway(false), _mHandShake(false)
{
}

Clients::Clients(const Clients& src) 
: _mNickName(src.getNick()), _mUserName(src.getUser()), _mHostName(src.getHost()),
_mServerName(src.getServer()), _mRealName(src.getReal()), _mAwayMessage(src._mAwayMessage), 
_mStream(src._mStream), _mAway(src.getAway()), _mHandShake(src.getHandShake())
{
}



Clients::~Clients()
{
}


void            Clients::setNick(const std::string& s) {_mNickName = s;}
void            Clients::setUser(const std::string& s) {_mUserName = s;}
void            Clients::setHost(const std::string& s) {_mHostName = s;}
void            Clients::setServer(const std::string& s) {_mServerName = s;}
void            Clients::setReal(const std::string& s) {_mRealName = s;}
void            Clients::setAwayMessage(const std::string& s) {_mAwayMessage = s;}
void            Clients::setAway(bool status) {_mAway = status;}
void            Clients::setHandShake() {_mHandShake = true;}

std::string     Clients::getNick() const {return _mNickName;}
std::string     Clients::getUser() const {return _mUserName;}
std::string     Clients::getHost() const {return _mHostName;}
std::string     Clients::getServer() const {return _mServerName;}
std::string     Clients::getReal() const {return _mRealName;}
std::string     Clients::getAwayMessage() const {return _mAwayMessage;}
TcpStream&      Clients::getStream() {return _mStream;}
bool            Clients::getAway() const {return _mAway;}
bool            Clients::getHandShake() const {return _mHandShake;}


std::ostream&   operator<<(std::ostream& o, const Clients & src)
{
    o << "Nick = " << src.getNick() << std::endl;
    o << "User = " << src.getUser() << std::endl;
    o << "Host = " << src.getHost() << std::endl;
    o << "Server = " << src.getServer() << std::endl;
    o << "Real = " << src.getReal() << std::endl;
    return o;
}
