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
        void    setPasswordUsedToConnect(const std::string& s);
        void    setUser(const std::string& s);
        void    setHost(const std::string& s);
        void    setServer(const std::string& s);
        void    setReal(const std::string& s);
        void    setAway(bool status);
        void    setAwayMsg(std::string msg);

        std::string     getNick() const;
        std::string     getUser() const;
        std::string     getHost() const;
        std::string     getServer() const;
        std::string     getReal() const;
        TcpStream&      getStream() const;
        bool            getAway() const;
        std::string     getAwayMsg() const;
        std::string     getPasswordUsedToConnect() const;

        bool hasSetIncorrectPassword(const std::string serverPassword) const;

    private:
        std::string nickname_;
        std::string username_;
        std::string hostname_;
        std::string servername_;
        std::string realname_;
        TcpStream*  stream_;
        bool        away_;
        std::string awayMsg_;
        std::string passwordUsedToConnect_;

        Client();
};

std::ostream&   operator << (std::ostream& o, const Client& src);


#endif