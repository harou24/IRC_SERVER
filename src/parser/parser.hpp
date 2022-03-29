#ifndef PARSER_HPP
# define PARSER_HPP

#include <utility>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>

struct IArgs {

    IArgs() : arg1(""), arg2(""), arg3(""), arg4("") {}
    IArgs&  operator=(const IArgs& x)
    {
        arg1 = x.arg1;
        arg2 = x.arg2;
        arg3 = x.arg3;
        arg4 = x.arg4;
        return *this;
    }
    virtual ~IArgs(){}
    std::string arg1;
    std::string arg2;
    std::string arg3;
    std::string arg4;
};

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

class Parser {
    private:

    public:
        Parser();
        ~Parser();
        void parse(const std::string &inProgram);
        IArgs&  getArgument();
        CommandType getCommand();
        std::string& getRaw();

    private:
        CommandType     _mCommand;
        IArgs          *_mArguments;
        std::string     _mRawText;

    private:
        std::string find_command(const std::string& s);
        void    away(const std::string& str);
        void    invite(const std::string& str);
        void    join(const std::string& str);
        void    me(const std::string& str);
        void    msg(const std::string& str);
        void    nick(const std::string& str);
        void    notice(const std::string& str);
        void    part(const std::string& str);
        void    privmsg(const std::string& str);
        void    query(const std::string& str);
        void    quit(const std::string& str);
        void    whois(const std::string& str);
        void    mode(const std::string& str);
        void    user(const std::string& str);
        void    ping(const std::string& str);
};

#endif