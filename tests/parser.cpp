#include <catch2/catch_all.hpp>

#include <iostream>

#include "parser.hpp"

TEST_CASE("Parsing command Nick")
{
    Parser::Parser p;
    Parser::Token *t;


    t = &p.parse("/NICK harou");

    REQUIRE(t->mType == Parser::NICK);
    REQUIRE(t->mParser->channel == "");
    REQUIRE(t->mParser->name == "harou");
    REQUIRE(t->mParser->message == "");
    REQUIRE(t->mParser->newtopic == "");
    REQUIRE(t->mParser->min == 0);
    REQUIRE(t->mParser->max == 0);

    // t->mParser->name;
}
