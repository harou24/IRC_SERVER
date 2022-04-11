#ifndef CMD_CONTROLLER_HPP
# define CMD_CONTROLLER_HPP

# include "commands.hpp"
# include "Server.hpp"

enum CommandType {
    AWAY,
    INVITE,
    JOIN,
    ME,
    MSG,
    NICK = nick,
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

class CmdController {

    private:
       const Server* const server;


    public:
        execute();

};

#endif