#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "parser.hpp"
#include "tcp_stream.hpp"


class Client
{
    public:
        Client(const std::string& nick, TcpStream *stream);
        Client(const Client& src);
        ~Client();

        void    setNick(const std::string& s);
        void    setUser(const std::string& s);
        void    setHost(const std::string& s);
        void    setServer(const std::string& s);
        void    setReal(const std::string& s);
        void    setHandShake();
        void    setAway(bool status);
        void    setAwayMsg(std::string msg);

        std::string     getNick() const;
        std::string     getUser() const;
        std::string     getHost() const;
        std::string     getServer() const;
        std::string     getReal() const;
        TcpStream&      getStream() const;
        bool            getHandShake() const;
        bool            getAway() const;
        std::string     getAwayMsg() const;

    private:
        std::string _mNickName;
        std::string _mUserName;
        std::string _mHostName;
        std::string _mServerName;
        std::string _mRealName;
        TcpStream   *_mStream;
        bool        _mHandShake;
        bool        _mAway;
        std::string _mAwayMsg;

        Client();
};

std::ostream&   operator << (std::ostream& o, const Client& src);


#endif