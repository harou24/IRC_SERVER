#include <catch2/catch_all.hpp>

#include <iostream>

#include "parser.hpp"

TEST_CASE("Parsing command Nick")
{
    Parser::Parser p;
    Parser::Token *t;


    t = &p.parse("/NICK name");

    REQUIRE(t->mType == Parser::NICK);
    REQUIRE(t->mParser->channel == "");
    REQUIRE(t->mParser->name == "name");
    REQUIRE(t->mParser->message == "");
    REQUIRE(t->mParser->newtopic == "");
    REQUIRE(t->mParser->min == 0);
    REQUIRE(t->mParser->max == 0);
}

TEST_CASE("Parsing command JOIN")
{
    Parser::Parser p;
    Parser::Token *t;


    t = &p.parse("/JOIN #channel");

    REQUIRE(t->mType == Parser::JOIN);
    REQUIRE(t->mParser->channel == "#channel");
    REQUIRE(t->mParser->name == "");
    REQUIRE(t->mParser->message == "");
    REQUIRE(t->mParser->newtopic == "");
    REQUIRE(t->mParser->min == 0);
    REQUIRE(t->mParser->max == 0);
}

TEST_CASE("Parsing command AWAY")
{
    Parser::Parser p;
    Parser::Token *t;


    t = &p.parse("/AWAY message");

    REQUIRE(t->mType == Parser::AWAY);
    REQUIRE(t->mParser->channel == "");
    REQUIRE(t->mParser->name == "");
    REQUIRE(t->mParser->message == "message");
    REQUIRE(t->mParser->newtopic == "");
    REQUIRE(t->mParser->min == 0);
    REQUIRE(t->mParser->max == 0);
}

TEST_CASE("Parsing command INVITE")
{
    Parser::Parser p;
    Parser::Token *t;


    t = &p.parse("/INVITE name #channel");

    REQUIRE(t->mType == Parser::INVITE);
    REQUIRE(t->mParser->channel == "#channel");
    REQUIRE(t->mParser->name == "name");
    REQUIRE(t->mParser->message == "");
    REQUIRE(t->mParser->newtopic == "");
    REQUIRE(t->mParser->min == 0);
    REQUIRE(t->mParser->max == 0);
}

TEST_CASE("Parsing command MSG")
{
    Parser::Parser p;
    Parser::Token *t;


    t = &p.parse("/MSG name message");

    REQUIRE(t->mType == Parser::MSG);
    REQUIRE(t->mParser->channel == "");
    REQUIRE(t->mParser->name == "name");
    REQUIRE(t->mParser->message == "message");
    REQUIRE(t->mParser->newtopic == "");
    REQUIRE(t->mParser->min == 0);
    REQUIRE(t->mParser->max == 0);
}

TEST_CASE("Parsing command ME")
{
    Parser::Parser p;
    Parser::Token *t;


    t = &p.parse("/ME message");

    REQUIRE(t->mType == Parser::ME);
    REQUIRE(t->mParser->channel == "");
    REQUIRE(t->mParser->name == "");
    REQUIRE(t->mParser->message == "message");
    REQUIRE(t->mParser->newtopic == "");
    REQUIRE(t->mParser->min == 0);
    REQUIRE(t->mParser->max == 0);
}

TEST_CASE("Parsing command NOTICE")
{
    Parser::Parser p;
    Parser::Token *t;


    t = &p.parse("/NOTICE name message");

    REQUIRE(t->mType == Parser::NOTICE);
    REQUIRE(t->mParser->channel == "");
    REQUIRE(t->mParser->name == "name");
    REQUIRE(t->mParser->message == "message");
    REQUIRE(t->mParser->newtopic == "");
    REQUIRE(t->mParser->min == 0);
    REQUIRE(t->mParser->max == 0);
}

TEST_CASE("Parsing command PART")
{
    Parser::Parser p;
    Parser::Token *t;


    t = &p.parse("/PART #channel");

    REQUIRE(t->mType == Parser::PART);
    REQUIRE(t->mParser->channel == "#channel");
    REQUIRE(t->mParser->name == "");
    REQUIRE(t->mParser->message == "");
    REQUIRE(t->mParser->newtopic == "");
    REQUIRE(t->mParser->min == 0);
    REQUIRE(t->mParser->max == 0);
}

TEST_CASE("Parsing command PRIVMSG")
{
    Parser::Parser p;
    Parser::Token *t;


    t = &p.parse("/PRIVMSG name message");

    REQUIRE(t->mType == Parser::PRIVMSG);
    REQUIRE(t->mParser->channel == "");
    REQUIRE(t->mParser->name == "name");
    REQUIRE(t->mParser->message == "message");
    REQUIRE(t->mParser->newtopic == "");
    REQUIRE(t->mParser->min == 0);
    REQUIRE(t->mParser->max == 0);
}

TEST_CASE("Parsing command QUERY")
{
    Parser::Parser p;
    Parser::Token *t;


    t = &p.parse("/QUERY name message");

    REQUIRE(t->mType == Parser::QUERY);
    REQUIRE(t->mParser->channel == "");
    REQUIRE(t->mParser->name == "name");
    REQUIRE(t->mParser->message == "message");
    REQUIRE(t->mParser->newtopic == "");
    REQUIRE(t->mParser->min == 0);
    REQUIRE(t->mParser->max == 0);
}

TEST_CASE("Parsing command QUIT")
{
    Parser::Parser p;
    Parser::Token *t;


    t = &p.parse("/QUIT message");

    REQUIRE(t->mType == Parser::QUIT);
    REQUIRE(t->mParser->channel == "");
    REQUIRE(t->mParser->name == "");
    REQUIRE(t->mParser->message == "message");
    REQUIRE(t->mParser->newtopic == "");
    REQUIRE(t->mParser->min == 0);
    REQUIRE(t->mParser->max == 0);
}

TEST_CASE("Parsing command WHOIS")
{
    Parser::Parser p;
    Parser::Token *t;


    t = &p.parse("/WHOIS name");

    REQUIRE(t->mType == Parser::WHOIS);
    REQUIRE(t->mParser->channel == "");
    REQUIRE(t->mParser->name == "name");
    REQUIRE(t->mParser->message == "");
    REQUIRE(t->mParser->newtopic == "");
    REQUIRE(t->mParser->min == 0);
    REQUIRE(t->mParser->max == 0);
}
