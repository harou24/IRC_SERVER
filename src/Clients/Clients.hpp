#ifndef CLIENETS_HPP
# define CLIENETS_HPP

#include "parser.hpp"
#include "TcpStream.hpp"


class Clients
{
public:
    Clients(const std::string& nick, size_t fd);
    ~Clients();

    void    setNick(const std::string& s);
    void    setUser(const std::string& s);
    void    setHost(const std::string& s);
    void    setServer(const std::string& s);
    void    setReal(const std::string& s);

    std::string     getNick() const;
    std::string     getUser() const;
    std::string     getHost() const;
    std::string     getServer() const;
    std::string     getReal() const;
    size_t          getFD() const;

private:
    std::string  _mNickName;
    std::string  _mUserName;
    std::string  _mHostName;
    std::string  _mServerName;
    std::string  _mRealName;
    TcpStream    _mStream;

private:
    Clients();
};

std::ostream&   operator<<(std::ostream& o, const Clients& src);


#endif