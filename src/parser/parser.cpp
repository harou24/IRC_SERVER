#include "parser.hpp"

#include <algorithm>

void    Parser::away(const std::string& str) 
{
    std::istringstream  ss(str);
    std::string         word;
    ss>>this->arguments_->arg1;
    while (ss>>word)
        this->arguments_->arg1 += " " + word;
    if (this->arguments_->arg1[0] != ':' && this->arguments_->arg1 != "")
        this->command_ = UNKNOWN;
}

void    Parser::invite(const std::string& str)
{
    std::istringstream  ss(str);
    ss >> this->arguments_->arg1;
    ss >> this->arguments_->arg2;
    if (this->arguments_->arg2 == "" || this->arguments_->arg2[0] != '#' || ss >> this->arguments_->arg3)
        this->command_ = UNKNOWN;
}

void    Parser::join(const std::string& str) 
{
    std::istringstream  ss(str);
    ss >> this->arguments_->arg1;
    ss >> this->arguments_->arg2;
    if (this->arguments_->arg1[0] != '#' || ss >> this->arguments_->arg3)
        this->command_ = UNKNOWN;
}

void    Parser::nick(const std::string& str) 
{
    std::istringstream  ss(str);
    ss >> this->arguments_->arg1;
    if (ss >> this->arguments_->arg2)
        this->command_ = UNKNOWN;
}

void    Parser::pass(const std::string& str) 
{
    std::istringstream  ss(str);
    ss >> this->arguments_->arg1;
    if (ss >> this->arguments_->arg2)
        this->command_ = UNKNOWN;
}

void    Parser::notice(const std::string& str) 
{
    std::istringstream  ss(str);
    std::string         word;
    ss >> this->arguments_->arg1;
    ss>>this->arguments_->arg2;
    while (ss>>word)
        this->arguments_->arg2 += " " + word;
    if (this->arguments_->arg2 == "" || this->arguments_->arg2[0] != ':')
        this->command_ = UNKNOWN;
}

void    Parser::pong(const std::string& str) 
{
    std::istringstream  ss(str);
    ss >> this->arguments_->arg1;
}

void    Parser::privmsg(const std::string& str) 
{
    std::istringstream  ss(str);
    std::string         word;
    ss >> this->arguments_->arg1;
    ss>>this->arguments_->arg2;
    while (ss>>word)
        this->arguments_->arg2 += " " + word;
    if (this->arguments_->arg2 == "" || this->arguments_->arg2[0] != ':')
        this->command_ = UNKNOWN;
}

void    Parser::quit(const std::string& str) 
{
    std::istringstream  ss(str);
    std::string         word;
    ss>>this->arguments_->arg1;
    while (ss>>word)
        this->arguments_->arg1 += " " + word;
    if (this->arguments_->arg1[0] != ':' && this->arguments_->arg1 != "")
        this->command_ = UNKNOWN;
}

void    Parser::mode(const std::string& str) 
{
    std::istringstream  ss(str);
    std::string word;
    ss >> this->arguments_->arg1;
    ss >> this->arguments_->arg2;
    ss >> this->arguments_->arg3;
    while (ss>>word)
        this->arguments_->arg3 += " " + word;
}

void    Parser::part(const std::string& str) 
{
    this->arguments_->arg1 = str;
}

void    Parser::kick(const std::string& str) 
{
    std::istringstream  ss(str);
    std::string         word;
    ss >> this->arguments_->arg1;
    ss >> this->arguments_->arg2;
    ss >> this->arguments_->arg3;

    while (ss>>word)
        this->arguments_->arg3 += " " + word;
}

void    Parser::topic(const std::string& str) 
{
    std::istringstream  ss(str);
    std::string         word;
    ss >> this->arguments_->arg1;
    ss>>this->arguments_->arg2;
    while (ss>>word)
        this->arguments_->arg2 += " " + word;
}

void    Parser::user(const std::string& str) 
{
    std::istringstream  ss(str);
    std::string         word;
    ss >> this->arguments_->arg1;
    ss >> this->arguments_->arg2;
    ss >> this->arguments_->arg3;
    ss >> this->arguments_->arg4;
    if (this->arguments_->arg4 != "" && this->arguments_->arg4[0] == ':')
    {
        while (ss>>word)
            this->arguments_->arg4 += " " + word;
    }
    if (this->arguments_->arg4[0] != ':' || this->arguments_->arg4 == "")
        this->command_ = UNKNOWN;
}

void    Parser::ping(const std::string& str) 
{
    std::istringstream  ss(str);
    ss >> this->arguments_->arg1;
}

Parser::Parser() : command_(UNKNOWN), arguments_(0), rawText_("")
{ 
    this->arguments_ = new Args();
}

Parser::~Parser() 
{
    delete arguments_;
}

Args& Parser::getArgument() const
{
    return *this->arguments_;
}

int Parser::getCommand() const
{
    return command_;
}

std::string Parser::getRaw() const
{
    return this->rawText_;
}

std::string Parser::findCommand(const std::string& s)
{
    std::string s1, s2 = "";
    std::istringstream  ss(s);
    std::map<std::string,CommandType> string_to_case;
    string_to_case.insert(std::make_pair<std::string,CommandType>("AWAY",AWAY)); 
    string_to_case.insert(std::make_pair<std::string,CommandType>("INVITE",INVITE));
    string_to_case.insert(std::make_pair<std::string,CommandType>("JOIN",JOIN)); 
    string_to_case.insert(std::make_pair<std::string,CommandType>("NICK",NICK)); 
    string_to_case.insert(std::make_pair<std::string,CommandType>("NOTICE",NOTICE));
    string_to_case.insert(std::make_pair<std::string,CommandType>("PONG",PONG));
    string_to_case.insert(std::make_pair<std::string,CommandType>("PRIVMSG",PRIVMSG));
    string_to_case.insert(std::make_pair<std::string,CommandType>("QUIT",QUIT));
    string_to_case.insert(std::make_pair<std::string,CommandType>("MODE",MODE));
    string_to_case.insert(std::make_pair<std::string,CommandType>("USER",USER));
    string_to_case.insert(std::make_pair<std::string,CommandType>("PING",PING));
    string_to_case.insert(std::make_pair<std::string,CommandType>("PART",PART));
    string_to_case.insert(std::make_pair<std::string,CommandType>("KICK",KICK));
    string_to_case.insert(std::make_pair<std::string,CommandType>("PASS",PASS));
    string_to_case.insert(std::make_pair<std::string,CommandType>("TOPIC",TOPIC));
    
    ss >> s1;
    if (ss>>s2)
        s2 = s.substr(s1.length()+1, s.length() - (s1.length()+1));

    for (std::string::iterator p = s1.begin(); s1.end() != p; ++p)
        *p = toupper(*p);

    if (s1 == "QUIT" || s1 == "AWAY" || s1 == "TOPIC" || (s1 == "PING" && s2 == ""))
        this->command_ = string_to_case.find(s1)->second;
    else if (string_to_case.find(s1) != string_to_case.end() && s2 != "")
        this->command_ = string_to_case.find(s1)->second;
    else
        this->command_ = UNKNOWN;
    return (s2);
}

void    Parser::parse(const std::string &inProgram)
{
    std::string arg = inProgram;

    arg.erase(std::remove(arg.begin(), arg.end(), '\r'), arg.end());

    void    (Parser::*p2f[])(const std::string& x) = {&Parser::pass, \
        &Parser::nick, &Parser::user, &Parser::away, &Parser::invite, \
        &Parser::join, &Parser::notice, &Parser::pong, &Parser::privmsg, \
        &Parser::quit, &Parser::mode, &Parser::ping, \
        &Parser::part, &Parser::kick, &Parser::topic};

    this->arguments_->arg1 = this->arguments_->arg2 = this->arguments_->arg3 = this->arguments_->arg4 = "";
    this->rawText_ = arg;

    
    if (arg != "CAP LS")
        arg = findCommand(arg);
    else
        this->command_ = CAP_LS;
    if (this->command_ < CAP_LS)
        (this->*p2f[this->command_])(arg);
    #if 1
        std::stringstream ss;
        ss << "command_ = " << this->command_;
        print("DEBUG", ss.str());
    #endif
}

std::ostream&   operator<<(std::ostream& o, Parser const& src)
{
    o << "command = " << src.getCommand() << std::endl;
    o << "argument1 = " << src.getArgument().arg1 << std::endl;
    o << "argument2 = " << src.getArgument().arg2 << std::endl;
    o << "argument3 = " << src.getArgument().arg3 << std::endl;
    o << "argument4 = " << src.getArgument().arg4 << std::endl;
    o << "rawtext = " << src.getRaw();

    return o;
}
