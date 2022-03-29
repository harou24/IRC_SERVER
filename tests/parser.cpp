#include <catch2/catch_all.hpp>

#include <iostream>

#include "parser.hpp"

TEST_CASE("Parsing command Nick")
{
    Parser   parser;
    
    parser.parse("nick lala ");

    IArgs A = parser.getArgument();

    REQUIRE(parser.getCommand() == NICK);
    REQUIRE(parser.getRaw() == "nick lala ");
    REQUIRE(A.arg1 == "lala");
    REQUIRE(A.arg2 == "");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
    
}

TEST_CASE("Parsing command JOIN")
{
    Parser   parser;
    
    parser.parse("JOIN #channel");

    IArgs A = parser.getArgument();

    REQUIRE(parser.getCommand() == JOIN);
    REQUIRE(parser.getRaw() == "JOIN #channel");
    REQUIRE(A.arg1 == "#channel");
    REQUIRE(A.arg2 == "");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command AWAY")
{
    Parser   parser;
    
    parser.parse("AWAY message");

    IArgs A = parser.getArgument();

    REQUIRE(parser.getCommand() == AWAY);
    REQUIRE(parser.getRaw() == "AWAY message");
    REQUIRE(A.arg1 == "message");
    REQUIRE(A.arg2 == "");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command INVITE")
{
    Parser   parser;
    
    parser.parse("INVITE name #channel");

    IArgs A = parser.getArgument();

    REQUIRE(parser.getCommand() == INVITE);
    REQUIRE(parser.getRaw() == "INVITE name #channel");
    REQUIRE(A.arg1 == "name");
    REQUIRE(A.arg2 == "#channel");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command MSG")
{
    Parser   parser;
    
    parser.parse("MSG name :message second");

    IArgs A = parser.getArgument();

    REQUIRE(parser.getCommand() == MSG);
    REQUIRE(parser.getRaw() == "MSG name :message second");
    REQUIRE(A.arg1 == "name");
    REQUIRE(A.arg2 == ":message second");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command ME")
{
    Parser   parser;
    
    parser.parse("ME :message second");

    IArgs A = parser.getArgument();

    REQUIRE(parser.getCommand() == ME);
    REQUIRE(parser.getRaw() == "ME :message second");
    REQUIRE(A.arg1 == ":message second");
    REQUIRE(A.arg2 == "");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command NOTICE")
{
    Parser   parser;
    
    parser.parse("NOTICE name :message second");
    
    IArgs A = parser.getArgument();

    REQUIRE(parser.getCommand() == NOTICE);
    REQUIRE(parser.getRaw() == "NOTICE name :message second");
    REQUIRE(A.arg1 == "name");
    REQUIRE(A.arg2 == ":message second");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command PART")
{
    Parser   parser;
    
    parser.parse("PART #channel");

    IArgs A = parser.getArgument();

    REQUIRE(parser.getCommand() == PART);
    REQUIRE(parser.getRaw() == "PART #channel");
    REQUIRE(A.arg1 == "#channel");
    REQUIRE(A.arg2 == "");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command PRIVMSG")
{
    Parser   parser;
    
    parser.parse("PRIVMSG name message");

    IArgs A = parser.getArgument();

    REQUIRE(parser.getCommand() == PRIVMSG);
    REQUIRE(parser.getRaw() == "PRIVMSG name message");
    REQUIRE(A.arg1 == "name");
    REQUIRE(A.arg2 == "message");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command QUERY")
{
    Parser   parser;
    
    parser.parse("QUERY name message");

    IArgs A = parser.getArgument();

    REQUIRE(parser.getCommand() == QUERY);
    REQUIRE(parser.getRaw() == "QUERY name message");
    REQUIRE(A.arg1 == "name");
    REQUIRE(A.arg2 == "message");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command QUIT")
{
    Parser   parser;
    
    parser.parse("QUIT message");

    IArgs A = parser.getArgument();

    REQUIRE(parser.getCommand() == QUIT);
    REQUIRE(parser.getRaw() == "QUIT message");
    REQUIRE(A.arg1 == "message");
    REQUIRE(A.arg2 == "");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command WHOIS")
{
    Parser   parser;
    
    parser.parse("WHOIS name");

    IArgs A = parser.getArgument();

    REQUIRE(parser.getCommand() == WHOIS);
    REQUIRE(parser.getRaw() == "WHOIS name");
    REQUIRE(A.arg1 == "name");
    REQUIRE(A.arg2 == "");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command MODE1")
{
    Parser   parser;
    
    parser.parse("MODE name -b <nick>");

    IArgs A = parser.getArgument();

    REQUIRE(parser.getCommand() == MODE);
    REQUIRE(parser.getRaw() == "MODE name -b <nick>");
    REQUIRE(A.arg1 == "name");
    REQUIRE(A.arg2 == "-b");
    REQUIRE(A.arg3 == "<nick>");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command MODE2")
{
    Parser   parser;
    
    parser.parse("MODE #channel -b <nick>");

    IArgs A = parser.getArgument();

    REQUIRE(parser.getCommand() == MODE);
    REQUIRE(parser.getRaw() == "MODE #channel -b <nick>");
    REQUIRE(A.arg1 == "#channel");
    REQUIRE(A.arg2 == "-b");
    REQUIRE(A.arg3 == "<nick>");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command USER")
{
    Parser   parser;
    
    parser.parse("USER name hostname servername :real name");

    IArgs A = parser.getArgument();

    REQUIRE(parser.getCommand() == USER);
    REQUIRE(parser.getRaw() == "USER name hostname servername :real name");
    REQUIRE(A.arg1 == "name");
    REQUIRE(A.arg2 == "hostname");
    REQUIRE(A.arg3 == "servername");
    REQUIRE(A.arg4 == ":real name");
}

TEST_CASE("Parsing command PING")
{
    Parser   parser;
    
    parser.parse("PING hostname");

    IArgs A = parser.getArgument();

    REQUIRE(parser.getCommand() == PING);
    REQUIRE(parser.getRaw() == "PING hostname");
    REQUIRE(A.arg1 == "hostname");
    REQUIRE(A.arg2 == "");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}