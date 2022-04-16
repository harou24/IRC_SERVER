#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "irc_server.hpp"
# include "parser.hpp"
# include "cmd_controller.hpp"

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

std::string    nick(CmdController* controller);
std::string    user(CmdController* controller);
std::string    ping(CmdController* controller);

#endif