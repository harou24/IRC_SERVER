#include "parser.hpp"

#include <iostream>

namespace Parser{

Parser::Parser(void)
{ 
    std::cout << "Parser !\n";
}

Parser::~Parser(void) { }

std::pair<CommandType, std::string> find_command(const std::string& s)
    {
        size_t         start = 1, end = s.find(" ");
        std::string s1, s2;
        CommandType command;
        std::map<std::string,CommandType> string_to_case;
        string_to_case.insert(std::make_pair<std::string,CommandType>("AWAY",AWAY)); 
        string_to_case.insert(std::make_pair<std::string,CommandType>("JOIN",JOIN)); 
        // string_to_case.insert(std::make_pair<std::string,CommandType>("LIST",LIST)); 
        string_to_case.insert(std::make_pair<std::string,CommandType>("NICK",NICK)); 
        string_to_case.insert(std::make_pair<std::string,CommandType>("MSG",MSG));
        string_to_case.insert(std::make_pair<std::string,CommandType>("INVITE",INVITE));
        string_to_case.insert(std::make_pair<std::string,CommandType>("ME",ME));
        string_to_case.insert(std::make_pair<std::string,CommandType>("NOTICE",NOTICE));
        string_to_case.insert(std::make_pair<std::string,CommandType>("PART",PART));
        string_to_case.insert(std::make_pair<std::string,CommandType>("PRIVMSG",PRIVMSG));
        string_to_case.insert(std::make_pair<std::string,CommandType>("QUERY",QUERY));
        string_to_case.insert(std::make_pair<std::string,CommandType>("QUIT",QUIT));
        string_to_case.insert(std::make_pair<std::string,CommandType>("WHOIS",WHOIS));
        s1 = s.substr(start, end - start);
        s2 = s.substr(end +1, s.length() - (end +1));

        for (std::string::iterator p = s1.begin(); s1.end() != p; ++p)
            *p = toupper(*p);

        if (s1 == "QUIT" || s1 == "AWAY")
            command = string_to_case.find(s1)->second;
        else if (string_to_case.find(s1) != string_to_case.end() && (end +1) <= s.length())
            command = string_to_case.find(s1)->second;
        else
            command = UNKOWN;
        return (std::make_pair(command, s2));
    }

    Token& Parser::parse(const std::string &inProgram)
    {
        Token   *currentToken = new Token();
        currentToken->mRawText = inProgram;
        std::pair<CommandType, std::string> split_str;
        if (inProgram[0] == '/'){
            split_str = find_command(inProgram);
            switch(split_str.first){
                case AWAY:
                    currentToken->mType = AWAY;
                    currentToken->mParser = new away(split_str.second);
                    break;
                case JOIN:
                    currentToken->mParser = new join(split_str.second);
                    if (currentToken->mParser->channel != "")
                        currentToken->mType = JOIN;
                    break;
                case LIST:
                    currentToken->mType = LIST;
                    currentToken->mParser = new list(split_str.second);
                    break;
                case NICK:
                    currentToken->mParser = new nick(split_str.second);
                    currentToken->mType = NICK;
                    break;
                case MSG:
                    currentToken->mParser = new msg(split_str.second);
                    if (currentToken->mParser->name != "")    
                        currentToken->mType = MSG;
                    break;
                case INVITE:
                    currentToken->mParser = new invite(split_str.second);
                    if (currentToken->mParser->name != "")    
                        currentToken->mType = INVITE;
                    break;
                case ME:
                    currentToken->mParser = new me(split_str.second);
                    if (currentToken->mParser->message != "")    
                        currentToken->mType = ME;
                    break;
                case NOTICE:
                    currentToken->mParser = new notice(split_str.second);
                    if (currentToken->mParser->message != "")    
                        currentToken->mType = NOTICE;
                    break;
                case PART:
                    currentToken->mParser = new part(split_str.second);
                    if (currentToken->mParser->channel != "")    
                        currentToken->mType = PART;
                    break;
                case PRIVMSG:
                    currentToken->mParser = new privmsg(split_str.second);
                    if (currentToken->mParser->message != "")    
                        currentToken->mType = PRIVMSG;
                    break;
                case QUERY:
                    currentToken->mParser = new query(split_str.second);
                    if (currentToken->mParser->message != "")    
                        currentToken->mType = QUERY;
                    break;
                case QUIT:
                    currentToken->mParser = new quit(split_str.second);
                    currentToken->mType = QUIT;
                    break;
                case WHOIS:
                    currentToken->mType = WHOIS;
                    currentToken->mParser = new whois(split_str.second);
                    break;
                
                default:
                    break; 
            }
        }
        return *currentToken;
    }
}