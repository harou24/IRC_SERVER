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
        UNKOWN,
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
            CommandType     mCommand;
            IArgs          *mArguments;
            std::string     mRawText;

        private:
            std::string find_command(const std::string& s);
            void    away(const std::string& x);
            void    invite(const std::string& x);
            void    join(const std::string& x);
            void    me(const std::string& x);
            void    msg(const std::string& x);
            void    nick(const std::string& x);
            void    notice(const std::string& x);
            void    part(const std::string& x);
            void    privmsg(const std::string& x);
            void    query(const std::string& x);
            void    quit(const std::string& x);
            void    whois(const std::string& x);
            void    mode(const std::string& x);
            void    user(const std::string& x);
            void    ping(const std::string& x);
    };

#endif