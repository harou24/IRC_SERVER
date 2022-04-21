#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "cmd_controller.hpp"

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

std::string    welcome(CmdController* controller);
std::string    nick(CmdController* controller);
std::string    user(CmdController* controller);
std::string    ping(CmdController* controller);

#endif