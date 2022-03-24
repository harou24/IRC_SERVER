#include <catch2/catch_all.hpp>

#include <iostream>

#include "TcpStream.hpp"
#include "TcpConnector.hpp"
#include "TcpAcceptor.hpp"

TEST_CASE("Class instantiates")
{
    TcpStream       stream;
    // TcpConnector    client;
    TcpAcceptor     server(8080, "127.0.0.1");
}