#include <catch2/catch_all.hpp>
#include "TcpStream.hpp"

TEST_CASE("Test constructor")
{
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    TcpStream stream(5, &address);

    REQUIRE(stream.getSd() == 5);
    REQUIRE(stream.getPeerIP() == "0.0.0.0");
    REQUIRE(stream.getPeerPort() == 0);
}