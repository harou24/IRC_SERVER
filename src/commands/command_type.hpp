#ifndef COMMAND_TYPE_HPP
# define COMMAND_TYPE_HPP

 enum CommandType {
    AWAY,
    INVITE,
    JOIN,
    ME,
    MSG,
    NICK,
    NOTICE,
    PONG,
    PRIVMSG,
    QUERY,
    QUIT,
    WHOIS,
    MODE,
    USER,
    PING,
    PART,
    KICK,
    CAP_LS,
    PASS,
    UNKNOWN,
    SIZE
};

#endif