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

std::string    nick(const IrcServer* const s);
std::string    away(const IrcServer* const s);
std::string    invite(const IrcServer* const s);
std::string    join(const IrcServer* const s);
std::string    me(const IrcServer* const s);
std::string    msg(const IrcServer* const s);
std::string    nick(const IrcServer* const s);
std::string    notice(const IrcServer* const s);
std::string    part(const IrcServer* const s);
std::string    privmsg(const IrcServer* const s);
std::string    query(const IrcServer* const s);
std::string    quit(const IrcServer* const s);
std::string    whois(const IrcServer* const s);
std::string    mode(const IrcServer* const s);
std::string    user(const IrcServer* const s);
std::string    ping(const IrcServer* const s);

#endif