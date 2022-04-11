#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "IrcServer.hpp"
# include "parser.hpp"

/*
enum CommandType {
    AWAY,
    INVITE,
    JOIN,
    ME,
    MSG,
    NICK,
    NOTICE,
    PART,
    PRIVMSG,
    QUERY,
    QUIT,
    WHOIS,
    MODE,
    USER,
    PING,
    UNKNOWN,
    SIZE
};
*/
std::string    nick(const IrcServer* const s);


#endif