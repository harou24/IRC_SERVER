#include "parser.hpp"
#include <iostream>

int main()
{
    Parser::Parser   T;
    Parser::Token *token;

    token = &T.parse("/quit #HAROU yo blabla");

    std::cout << token->mType << std::endl;
    std::cout << token->mRawText << std::endl;
    std::cout << token->mParser->message << std::endl;
    std::cout << token->mParser->channel << std::endl;
    std::cout << token->mParser->name << std::endl;

}
