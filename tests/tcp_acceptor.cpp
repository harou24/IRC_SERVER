#include <catch2/catch_all.hpp>
#include "TcpAcceptor.hpp"

TEST_CASE("Test constructor")
{
    TcpAcceptor acceptor(8080, "127.0.0.1");

    REQUIRE(acceptor.getListenSd() == 0);
    REQUIRE(acceptor.getPort() == 8080);
    REQUIRE(acceptor.getAddress() == "127.0.0.1");
}

TEST_CASE("Test init"){
    TcpAcceptor acceptor(8080, "127.0.0.1");
    
    acceptor.init();

    REQUIRE(acceptor.getListenSd() > 2);
    REQUIRE(acceptor.isListening());    
}

TEST_CASE("Test listen"){
    TcpAcceptor acceptor(8080, "127.0.0.1");
    int val;
    socklen_t length = sizeof(val);

    acceptor.init();
    getsockopt(acceptor.getListenSd(), SOL_SOCKET, SO_ACCEPTCONN, &val, &length);
    REQUIRE(val);
}