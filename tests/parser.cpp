#include <catch2/catch_all.hpp>

#include <iostream>

#include "parser.hpp"

TEST_CASE("Parsing command Nick")
{
    Parser   T;
    
    T.parse("nick lala ");

    IArgs A = T.getArgument();

    REQUIRE(T.getCommand() == NICK);
    REQUIRE(T.getRaw() == "nick lala ");
    REQUIRE(A.arg1 == "lala");
    REQUIRE(A.arg2 == "");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
    
}

TEST_CASE("Parsing command JOIN")
{
    Parser   T;
    
    T.parse("JOIN #channel");

    IArgs A = T.getArgument();

    REQUIRE(T.getCommand() == JOIN);
    REQUIRE(T.getRaw() == "JOIN #channel");
    REQUIRE(A.arg1 == "#channel");
    REQUIRE(A.arg2 == "");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command AWAY")
{
    Parser   T;
    
    T.parse("AWAY :message");

    IArgs A = T.getArgument();

    REQUIRE(T.getCommand() == AWAY);
    REQUIRE(T.getRaw() == "AWAY :message");
    REQUIRE(A.arg1 == ":message");
    REQUIRE(A.arg2 == "");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command INVITE")
{
    Parser   T;
    
    T.parse("INVITE name #channel");

    IArgs A = T.getArgument();

    REQUIRE(T.getCommand() == INVITE);
    REQUIRE(T.getRaw() == "INVITE name #channel");
    REQUIRE(A.arg1 == "name");
    REQUIRE(A.arg2 == "#channel");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command MSG")
{
    Parser   T;
    
    T.parse("MSG name :message second");

    IArgs A = T.getArgument();

    REQUIRE(T.getCommand() == MSG);
    REQUIRE(T.getRaw() == "MSG name :message second");
    REQUIRE(A.arg1 == "name");
    REQUIRE(A.arg2 == ":message second");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command ME")
{
    Parser   T;
    
    T.parse("ME :message second");

    IArgs A = T.getArgument();

    REQUIRE(T.getCommand() == ME);
    REQUIRE(T.getRaw() == "ME :message second");
    REQUIRE(A.arg1 == ":message second");
    REQUIRE(A.arg2 == "");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command NOTICE")
{
    Parser   T;
    
    T.parse("NOTICE name :message second");
    
    IArgs A = T.getArgument();

    REQUIRE(T.getCommand() == NOTICE);
    REQUIRE(T.getRaw() == "NOTICE name :message second");
    REQUIRE(A.arg1 == "name");
    REQUIRE(A.arg2 == ":message second");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command PART")
{
    Parser   T;
    
    T.parse("PART #channel");

    IArgs A = T.getArgument();

    REQUIRE(T.getCommand() == PART);
    REQUIRE(T.getRaw() == "PART #channel");
    REQUIRE(A.arg1 == "#channel");
    REQUIRE(A.arg2 == "");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command PRIVMSG")
{
    Parser   T;
    
    T.parse("PRIVMSG name message");

    IArgs A = T.getArgument();

    REQUIRE(T.getCommand() == PRIVMSG);
    REQUIRE(T.getRaw() == "PRIVMSG name message");
    REQUIRE(A.arg1 == "name");
    REQUIRE(A.arg2 == "message");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command QUERY")
{
    Parser   T;
    
    T.parse("QUERY name message");

    IArgs A = T.getArgument();

    REQUIRE(T.getCommand() == QUERY);
    REQUIRE(T.getRaw() == "QUERY name message");
    REQUIRE(A.arg1 == "name");
    REQUIRE(A.arg2 == "message");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command QUIT")
{
    Parser   T;
    
    T.parse("QUIT message");

    IArgs A = T.getArgument();

    REQUIRE(T.getCommand() == QUIT);
    REQUIRE(T.getRaw() == "QUIT message");
    REQUIRE(A.arg1 == "message");
    REQUIRE(A.arg2 == "");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command WHOIS")
{
    Parser   T;
    
    T.parse("WHOIS name");

    IArgs A = T.getArgument();

    REQUIRE(T.getCommand() == WHOIS);
    REQUIRE(T.getRaw() == "WHOIS name");
    REQUIRE(A.arg1 == "name");
    REQUIRE(A.arg2 == "");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command MODE1")
{
    Parser   T;
    
    T.parse("MODE name -b <nick>");

    IArgs A = T.getArgument();

    REQUIRE(T.getCommand() == MODE);
    REQUIRE(T.getRaw() == "MODE name -b <nick>");
    REQUIRE(A.arg1 == "name");
    REQUIRE(A.arg2 == "-b");
    REQUIRE(A.arg3 == "<nick>");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command MODE2")
{
    Parser   T;
    
    T.parse("MODE #channel -b <nick>");

    IArgs A = T.getArgument();

    REQUIRE(T.getCommand() == MODE);
    REQUIRE(T.getRaw() == "MODE #channel -b <nick>");
    REQUIRE(A.arg1 == "#channel");
    REQUIRE(A.arg2 == "-b");
    REQUIRE(A.arg3 == "<nick>");
    REQUIRE(A.arg4 == "");
}

TEST_CASE("Parsing command USER")
{
    Parser   T;
    
    T.parse("USER name hostname servername :real name");

    IArgs A = T.getArgument();

    REQUIRE(T.getCommand() == USER);
    REQUIRE(T.getRaw() == "USER name hostname servername :real name");
    REQUIRE(A.arg1 == "name");
    REQUIRE(A.arg2 == "hostname");
    REQUIRE(A.arg3 == "servername");
    REQUIRE(A.arg4 == ":real name");
}

TEST_CASE("Parsing command PING")
{
    Parser   T;
    
    T.parse("PING hostname");

    IArgs A = T.getArgument();

    REQUIRE(T.getCommand() == PING);
    REQUIRE(T.getRaw() == "PING hostname");
    REQUIRE(A.arg1 == "hostname");
    REQUIRE(A.arg2 == "");
    REQUIRE(A.arg3 == "");
    REQUIRE(A.arg4 == "");
}