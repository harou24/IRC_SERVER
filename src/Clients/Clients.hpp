#ifndef CLIENETS_HPP
# define CLIENETS_HPP

#include "parser.hpp"
#include "TcpStream.hpp"


class Clients
{
public:
    Clients(const std::string& nick, TcpStream &stream);
    Clients(const Clients& src);
    ~Clients();

    void    setNick(const std::string& s);
    void    setUser(const std::string& s);
    void    setHost(const std::string& s);
    void    setServer(const std::string& s);
    void    setReal(const std::string& s);
    void    setAwayMessage(const std::string& s);
    void    setAway(bool status);
    void    setHandShake();

    std::string     getNick() const;
    std::string     getUser() const;
    std::string     getHost() const;
    std::string     getServer() const;
    std::string     getReal() const;
    std::string     getAwayMessage() const;
    TcpStream&      getStream();
    bool            getAway() const;
    bool            getHandShake() const;

private:
    std::string _mNickName;
    std::string _mUserName;
    std::string _mHostName;
    std::string _mServerName;
    std::string _mRealName;
    std::string _mAwayMessage;
    TcpStream   _mStream;
    bool        _mAway;
    bool        _mHandShake;

private:
    Clients();
};

std::ostream&   operator<<(std::ostream& o, const Clients& src);


#endif