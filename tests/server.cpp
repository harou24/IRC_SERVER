#include <catch2/catch_all.hpp>

#include <iostream>


#include "Server.hpp"

TEST_CASE("Server constructor")
{
    Server serv(8080, "password");
    REQUIRE(serv.getPassword() == "password");
    REQUIRE(serv.isRunning() == false);
    REQUIRE(serv.getQueue().size() == 0);
    REQUIRE(serv.getClients().size() == 0);
}
