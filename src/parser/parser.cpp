#include "parser.hpp"

#include <iostream>


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


void    Parser::part(const std::string& str) 
{
    std::istringstream  ss(str);
    ss >> this->_mArguments->arg1;
    if (this->_mArguments->arg1[0] != '#' || ss >> this->_mArguments->arg2)
        this->_mCommand = UNKNOWN;
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
    if (ss >> this->_mArguments->arg1)
        this->_mCommand = UNKNOWN;
}

Parser::Parser() : _mCommand(UNKNOWN), _mArguments(0), _mRawText("")
{ 
    this->_mArguments = new IArgs();
}

Parser::~Parser() 
{
    delete _mArguments;
}

IArgs& Parser::getArgument()
{
    return *this->_mArguments;
}

CommandType Parser::getCommand()
{
    return _mCommand;
}

std::string& Parser::getRaw()
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
    string_to_case.insert(std::make_pair<std::string,CommandType>("PART",PART));
    string_to_case.insert(std::make_pair<std::string,CommandType>("PRIVMSG",PRIVMSG));
    string_to_case.insert(std::make_pair<std::string,CommandType>("QUERY",QUERY));
    string_to_case.insert(std::make_pair<std::string,CommandType>("QUIT",QUIT));
    string_to_case.insert(std::make_pair<std::string,CommandType>("WHOIS",WHOIS));
    string_to_case.insert(std::make_pair<std::string,CommandType>("MODE",MODE));
    string_to_case.insert(std::make_pair<std::string,CommandType>("USER",USER));
    string_to_case.insert(std::make_pair<std::string,CommandType>("PING",PING));
    
    ss >> s1;
    if (ss>>s2)
        s2 = s.substr(s1.length()+1, s.length() - (s1.length()+1));

    for (std::string::iterator p = s1.begin(); s1.end() != p; ++p)
        *p = toupper(*p);

    if (s1 == "QUIT" || s1 == "AWAY")
        this->_mCommand = string_to_case.find(s1)->second;
    else if (string_to_case.find(s1) != string_to_case.end() && s2 != "")
        this->_mCommand = string_to_case.find(s1)->second;
    else
        this->_mCommand = UNKNOWN;
    return (s2);
}

void    Parser::parse(const std::string &inProgram)
{
    void    (Parser::*p2f[])(const std::string& x) = {&Parser::away, &Parser::invite, \
        &Parser::join, &Parser::me, &Parser::msg, &Parser::nick, &Parser::notice, \
        &Parser::part, &Parser::privmsg, &Parser::query, &Parser::quit, \
        &Parser::whois, &Parser::mode, &Parser::user, &Parser::ping};
    
    this->_mRawText = inProgram;
    std::string arg;
        arg = find_command(inProgram);
    if (this->_mCommand != UNKNOWN)
        (this->*p2f[this->_mCommand])(arg);
}
