#include "Clients.hpp"

Clients::Clients(const std::string& nick, size_t fd) : _mNickName(nick), _mUserName(""), _mHostName(""), _mServerName(""), _mRealName(""), _mFD(fd)
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

std::string     Clients::getNick() const {return _mNickName;}
std::string     Clients::getUser() const {return _mUserName;}
std::string     Clients::getHost() const {return _mHostName;}
std::string     Clients::getServer() const {return _mServerName;}
std::string     Clients::getReal() const {return _mRealName;}
size_t          Clients::getFD() const {return _mFD;}


std::ostream&   operator<<(std::ostream& o, const Clients & src)
{
    o << "User = " << src.getUser() << std::endl;
    o << "Host = " << src.getHost() << std::endl;
    o << "Server = " << src.getServer() << std::endl;
    o << "Real = " << src.getReal() << std::endl;
    o << "FD = " << src.getFD() << std::endl;
    return o;
}
