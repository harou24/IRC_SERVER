#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "irc_server.hpp"
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

std::string    nick(IrcServer* s);
std::string    away(IrcServer* s);
std::string    invite(IrcServer* s);
std::string    join(IrcServer* s);
std::string    me(IrcServer* s);
std::string    msg(IrcServer* s);
std::string    nick(IrcServer* s);
std::string    notice(IrcServer* s);
std::string    part(IrcServer* s);
std::string    privmsg(IrcServer* s);
std::string    query(IrcServer* s);
std::string    quit(IrcServer* s);
std::string    whois(IrcServer* s);
std::string    mode(IrcServer* s);
std::string    user(IrcServer* s);
std::string    ping(IrcServer* s);

#endif