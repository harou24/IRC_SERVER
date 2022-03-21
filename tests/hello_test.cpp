#include <catch2/catch.hpp>

#include <iostream>

#include "hello_world.hpp"

TEST_CASE("Class instantiates")
{
    HelloWorld h;
    h.printHello();
}
