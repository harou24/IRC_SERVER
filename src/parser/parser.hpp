#ifndef PARSER_HPP
# define PARSER_HPP

# include <map>
# include <sstream>

# include "commands.hpp"

struct Args {
    Args() : arg1(""), arg2(""), arg3(""), arg4("") {}

    std::string arg1;
    std::string arg2;
    std::string arg3;
    std::string arg4;
};

class Parser {
    private:

    public:
        Parser();
        ~Parser();
        void parse(const std::string &inProgram);
        Args&  getArgument() const;
        int getCommand() const;
        std::string getRaw() const;

    private:
        int         _mCommand;
        Args        *_mArguments;
        std::string _mRawText;

    private:
        std::string find_command(const std::string& s);
        void    away(const std::string& str);
        void    invite(const std::string& str);
        void    join(const std::string& str);
        void    me(const std::string& str);
        void    msg(const std::string& str);
        void    nick(const std::string& str);
        void    notice(const std::string& str);
        void    pong(const std::string& str);
        void    privmsg(const std::string& str);
        void    query(const std::string& str);
        void    quit(const std::string& str);
        void    whois(const std::string& str);
        void    mode(const std::string& str);
        void    user(const std::string& str);
        void    ping(const std::string& str);
        void    part(const std::string& str);
        void    kick(const std::string& str);
};

std::ostream&   operator<<(std::ostream& o, Parser const& src);

#endif