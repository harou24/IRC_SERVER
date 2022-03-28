#ifndef PARSER_HPP
# define PARSER_HPP

#include <utility>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>

namespace Parser{

    struct Iparse {

        virtual ~Iparse(){}
        std::string name;
        std::string message;
        std::string channel;
        std::string newtopic;
        size_t      min;
        size_t      max;

        protected:
            Iparse() : name(""), message(""), channel(""), newtopic(""), min(0), max(0) {}
    };

    struct away : public Iparse{
        away(const std::string& x) {message = x;}
        // std::string message;
    };

    struct invite : public Iparse{
        invite(const std::string& x)
        {         
            std::istringstream  ss(x);
            ss >> name;
            channel = x.substr(name.length()+1);
            if (channel[0] != '#')
            {
                channel = "";
                name = "";
            }
        }
        // std::string name;
        // std::string channel;
    };

    struct join : public Iparse{
        join(const std::string& x) 
        {
            std::istringstream  ss(x);
            ss >> channel;
            ss >> message;
            if (channel[0] != '#')
                channel = "";
        }
        // std::string channel;
        // possibly there is also a password, that will go in message
    };

    struct list : public Iparse{
        list(const std::string& x){ channel = x;}
        // std::string channel;
        // size_t      min;
        // size_t      max;
    };

    struct me : public Iparse{
        me(const std::string& x) {message = x;}
        // std::string message;
    };

    struct msg : public Iparse{
        msg(const std::string& x) 
        {
            if (x.length() == 0)
                return;
            std::istringstream  ss(x);
            ss >> name;
            message = x.substr(name.length()+1);
        }
        // std::string name;
        // std::string message;
    };

    struct nick : public Iparse{
        nick(const std::string& x) {name = x;}
        // std::string name;
    };

    struct notice : public Iparse{
        notice(const std::string& x) 
        {
            if (x.length() == 0)
                return;
            std::istringstream  ss(x);
            ss >> name;
            message = x.substr(name.length()+1);
        }
        // std::string name;
        // std::string message;
    };

    struct part : public Iparse{
        part(const std::string& x) 
        {
            if (x[0] == '#')
                channel = x;
        }
        // std::string channel;
    };

    struct privmsg : public Iparse{
        privmsg(const std::string& x) 
        {
            if (x.length() == 0)
                return;
            std::istringstream  ss(x);
            ss >> name;
            message = x.substr(name.length()+1);
        }
        // std::string name;
        // std::string message;
    };

    struct query : public Iparse{
        query(const std::string& x) 
        {
            if (x.length() == 0)
                return;
            std::istringstream  ss(x);
            ss >> name;
            message = x.substr(name.length()+1);
        }
        // std::string name;
        // std::string message;
    };

    struct quit : public Iparse{
        quit(const std::string& x) {message = x;}
        // std::string message;
    };

    struct topic : public Iparse{
        topic(const std::string& x) {name = x;}
        // std::string channel;
        // std::string newtopic;
    };

    struct whois : public Iparse{
        whois(const std::string& x) {name = x;}
        // std::string name;
    };

    struct kick : public Iparse{
        kick(const std::string& x) {name = x;}
        // std::string channel;
        // std::string name;
    };

    struct mode : public Iparse{
        mode(const std::string& x) {name = x;}
        // std::string channel;
        // std::string name;
    };


    enum CommandType {
        AWAY,
        INVITE,
        JOIN,
        LIST,
        ME,
        MSG,
        NICK,
        NOTICE,
        PART,
        PRIVMSG,
        QUERY,
        QUIT,
        TOPIC,
        WHOIS,
        KICK,
        MODE,
        USER,
        UNKOWN
    };

    struct Token{

        Token() : mType(UNKOWN), mParser(0), mId(""), mRawText("") {}

        Token(const std::string& x) : mType(UNKOWN), mParser(0), mId(""), mRawText(x) {}
        Token(const std::string& x, std::string id) : mType(UNKOWN), mParser(0), mId(id), mRawText(x) {}


        CommandType     mType;
        Iparse          *mParser;
        std::string     mId;
        std::string     mRawText;
    };

    class Parser {
        private:

        public:
            Parser(void);
            ~Parser(void);
            Token& parse(const std::string &inProgram);
    };

}
#endif