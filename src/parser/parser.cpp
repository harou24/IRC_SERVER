#include "parser.hpp"

#include <algorithm>

void    Parser::away(const std::string& str) 
{
    std::istringstream  ss(str);
    std::string         word;
    ss>>this->_mArguments->arg1;
    while (ss>>word)
        this->_mArguments->arg1 += " " + word;
    if (this->_mArguments->arg1[0] != ':' && this->_mArguments->arg1 != "")
        this->_mCommand = UNKNOWN;
}

void    Parser::invite(const std::string& str)
{
    std::istringstream  ss(str);
    ss >> this->_mArguments->arg1;
    ss >> this->_mArguments->arg2;
    if (this->_mArguments->arg2 == "" || this->_mArguments->arg2[0] != '#' || ss >> this->_mArguments->arg3)
        this->_mCommand = UNKNOWN;
}


void    Parser::join(const std::string& str) 
{
    std::istringstream  ss(str);
    ss >> this->_mArguments->arg1;
    ss >> this->_mArguments->arg2;
    if (this->_mArguments->arg1[0] != '#' || ss >> this->_mArguments->arg3)
        this->_mCommand = UNKNOWN;
}


void    Parser::me(const std::string& str) 
{
    std::istringstream  ss(str);
    std::string         word;
    ss>>this->_mArguments->arg1;
    while (ss>>word)
        this->_mArguments->arg1 += " " + word;
    if (this->_mArguments->arg1 == "" || this->_mArguments->arg1[0] != ':')
        this->_mCommand = UNKNOWN;
}

void    Parser::msg(const std::string& str) 
{
    std::istringstream  ss(str);
    std::string         word;
    ss >> this->_mArguments->arg1;
    ss>>this->_mArguments->arg2;
    while (ss>>word)
        this->_mArguments->arg2 += " " + word;
    if (this->_mArguments->arg2 == "" || this->_mArguments->arg2[0] != ':')
        this->_mCommand = UNKNOWN;
}


void    Parser::nick(const std::string& str) 
{
    std::istringstream  ss(str);
    ss >> this->_mArguments->arg1;
    if (ss >> this->_mArguments->arg2)
        this->_mCommand = UNKNOWN;
}

void    Parser::pass(const std::string& str) 
{
    std::istringstream  ss(str);
    ss >> this->_mArguments->arg1;
    if (ss >> this->_mArguments->arg2)
        this->_mCommand = UNKNOWN;
}

void    Parser::notice(const std::string& str) 
{
    std::istringstream  ss(str);
    std::string         word;
    ss >> this->_mArguments->arg1;
    ss>>this->_mArguments->arg2;
    while (ss>>word)
        this->_mArguments->arg2 += " " + word;
    if (this->_mArguments->arg2 == "" || this->_mArguments->arg2[0] != ':')
        this->_mCommand = UNKNOWN;
}


void    Parser::pong(const std::string& str) 
{
    std::istringstream  ss(str);
    ss >> this->_mArguments->arg1;
}

void    Parser::privmsg(const std::string& str) 
{
    std::istringstream  ss(str);
    std::string         word;
    ss >> this->_mArguments->arg1;
    ss>>this->_mArguments->arg2;
    while (ss>>word)
        this->_mArguments->arg2 += " " + word;
    if (this->_mArguments->arg2 == "" || this->_mArguments->arg2[0] != ':')
        this->_mCommand = UNKNOWN;
}


void    Parser::query(const std::string& str) 
{
    std::istringstream  ss(str);
    std::string         word;
    ss >> this->_mArguments->arg1;
    ss>>this->_mArguments->arg2;
    while (ss>>word)
        this->_mArguments->arg2 += " " + word;
    if (this->_mArguments->arg2 == "" || this->_mArguments->arg2[0] != ':')
        this->_mCommand = UNKNOWN;
}


void    Parser::quit(const std::string& str) 
{
    std::istringstream  ss(str);
    std::string         word;
    ss>>this->_mArguments->arg1;
    while (ss>>word)
        this->_mArguments->arg1 += " " + word;
    if (this->_mArguments->arg1[0] != ':' && this->_mArguments->arg1 != "")
        this->_mCommand = UNKNOWN;
}

void    Parser::whois(const std::string& str) 
{
    std::istringstream  ss(str);
    ss >> this->_mArguments->arg1;
    if (ss >> this->_mArguments->arg1)
        this->_mCommand = UNKNOWN;
}


void    Parser::mode(const std::string& str) 
{
    std::istringstream  ss(str);
    ss >> this->_mArguments->arg1;
    ss >> this->_mArguments->arg2;
    ss >> this->_mArguments->arg3;
    ss >> this->_mArguments->arg4;

    if (this->_mArguments->arg4 != "")
        this->_mCommand = UNKNOWN;
}

void    Parser::part(const std::string& str) 
{
    this->_mArguments->arg1 = str;
}

void    Parser::kick(const std::string& str) 
{
    std::istringstream  ss(str);
    std::string         word;
    ss >> this->_mArguments->arg1;
    ss >> this->_mArguments->arg2;
    ss >> this->_mArguments->arg3;

    while (ss>>word)
        this->_mArguments->arg3 += " " + word;
}

void    Parser::user(const std::string& str) 
{
    std::istringstream  ss(str);
    std::string         word;
    ss >> this->_mArguments->arg1;
    ss >> this->_mArguments->arg2;
    ss >> this->_mArguments->arg3;
    ss >> this->_mArguments->arg4;
    if (this->_mArguments->arg4 != "" && this->_mArguments->arg4[0] == ':'){
        while (ss>>word)
            this->_mArguments->arg4 += " " + word;
    }
    if (this->_mArguments->arg4[0] != ':' || this->_mArguments->arg4 == "")
        this->_mCommand = UNKNOWN;
}

void    Parser::ping(const std::string& str) 
{
    std::istringstream  ss(str);
    ss >> this->_mArguments->arg1;
}

Parser::Parser() : _mCommand(UNKNOWN), _mArguments(0), _mRawText("")
{ 
    this->_mArguments = new Args();
}

Parser::~Parser() 
{
    delete _mArguments;
}

Args& Parser::getArgument() const
{
    return *this->_mArguments;
}

int Parser::getCommand() const
{
    return _mCommand;
}

std::string Parser::getRaw() const
{
    return this->_mRawText;
}


std::string Parser::find_command(const std::string& s)
{
    std::string s1, s2 = "";
    std::istringstream  ss(s);
    std::map<std::string,CommandType> string_to_case;
    string_to_case.insert(std::make_pair<std::string,CommandType>("AWAY",AWAY)); 
    string_to_case.insert(std::make_pair<std::string,CommandType>("INVITE",INVITE));
    string_to_case.insert(std::make_pair<std::string,CommandType>("JOIN",JOIN)); 
    string_to_case.insert(std::make_pair<std::string,CommandType>("ME",ME));
    string_to_case.insert(std::make_pair<std::string,CommandType>("MSG",MSG));
    string_to_case.insert(std::make_pair<std::string,CommandType>("NICK",NICK)); 
    string_to_case.insert(std::make_pair<std::string,CommandType>("NOTICE",NOTICE));
    string_to_case.insert(std::make_pair<std::string,CommandType>("PONG",PONG));
    string_to_case.insert(std::make_pair<std::string,CommandType>("PRIVMSG",PRIVMSG));
    string_to_case.insert(std::make_pair<std::string,CommandType>("QUERY",QUERY));
    string_to_case.insert(std::make_pair<std::string,CommandType>("QUIT",QUIT));
    string_to_case.insert(std::make_pair<std::string,CommandType>("WHOIS",WHOIS));
    string_to_case.insert(std::make_pair<std::string,CommandType>("MODE",MODE));
    string_to_case.insert(std::make_pair<std::string,CommandType>("USER",USER));
    string_to_case.insert(std::make_pair<std::string,CommandType>("PING",PING));
    string_to_case.insert(std::make_pair<std::string,CommandType>("PART",PART));
    string_to_case.insert(std::make_pair<std::string,CommandType>("KICK",KICK));
    string_to_case.insert(std::make_pair<std::string,CommandType>("PASS",PASS));
    
    ss >> s1;
    if (ss>>s2)
        s2 = s.substr(s1.length()+1, s.length() - (s1.length()+1));

    for (std::string::iterator p = s1.begin(); s1.end() != p; ++p)
        *p = toupper(*p);

    if (s1 == "QUIT" || s1 == "AWAY" || (s1 == "PING" && s2 == ""))
        this->_mCommand = string_to_case.find(s1)->second;
    else if (string_to_case.find(s1) != string_to_case.end() && s2 != "")
        this->_mCommand = string_to_case.find(s1)->second;
    else
        this->_mCommand = UNKNOWN;
    return (s2);
}

void    Parser::parse(const std::string &inProgram)
{
    std::string arg = inProgram;

    arg.erase(std::remove(arg.begin(), arg.end(), '\r'), arg.end());

    void    (Parser::*p2f[])(const std::string& x) = {&Parser::away, &Parser::invite, \
        &Parser::join, &Parser::me, &Parser::msg, &Parser::nick, &Parser::notice, \
        &Parser::pong, &Parser::privmsg, &Parser::query, &Parser::quit, \
        &Parser::whois, &Parser::mode, &Parser::user, &Parser::ping, &Parser::part, &Parser::kick, &Parser::pass};

    this->_mArguments->arg1 = this->_mArguments->arg2 = this->_mArguments->arg3 = this->_mArguments->arg4 = "";
    this->_mRawText = arg;

    
    if (arg != "CAP LS")
        arg = find_command(arg);
    else if (arg == "CAP END"){
        #if 1
            print("DEBUG", "CAP END detected");
        #endif
    }
    else
        this->_mCommand = CAP_LS;
    if (this->_mCommand < CAP_LS)
        (this->*p2f[this->_mCommand])(arg);
    #if 1
        std::stringstream ss;
        ss << "_mCommand = " << this->_mCommand;
        print("DEBUG", ss.str());
    #endif
}

std::ostream&   operator<<(std::ostream& o, Parser const& src){
    o << "command = " << src.getCommand() << std::endl;
    o << "argument1 = " << src.getArgument().arg1 << std::endl;
    o << "argument2 = " << src.getArgument().arg2 << std::endl;
    o << "argument3 = " << src.getArgument().arg3 << std::endl;
    o << "argument4 = " << src.getArgument().arg4 << std::endl;
    o << "rawtext = " << src.getRaw();

    return o;
}

