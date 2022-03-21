#include <catch2/catch_all.hpp>

#include <iostream>

#include "hello_world.hpp"

TEST_CASE("Class instantiates")
{
    HelloWorld h;
    h.printHello();
}
