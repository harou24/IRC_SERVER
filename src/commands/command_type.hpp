#ifndef COMMAND_TYPE_HPP
# define COMMAND_TYPE_HPP

 enum CommandType {
    PASS,
    NICK,
    USER,
    AWAY,
    INVITE,
    JOIN,
    NOTICE,
    PONG,
    PRIVMSG,
    QUIT,
    MODE,
    PING,
    PART,
    KICK,
    TOPIC,
    CAP_LS,
    UNKNOWN,
    SIZE
};

#endif