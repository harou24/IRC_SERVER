#ifndef COMMAND_TYPE_HPP
# define COMMAND_TYPE_HPP

 enum CommandType {
    AWAY,
    INVITE,
    JOIN,
    NICK,
    NOTICE,
    PONG,
    PRIVMSG,
    QUIT,
    WHOIS, 
    MODE,
    USER,
    PING,
    PART,
    KICK,
    PASS,
    TOPIC,
    CAP_LS,
    UNKNOWN,
    SIZE
};

#endif