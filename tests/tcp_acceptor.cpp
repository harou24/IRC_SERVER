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

TEST_CASE("Test bind"){
    TcpAcceptor acceptor(8080, "127.0.0.1");

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    socklen_t length = sizeof(address);

    getsockname(acceptor.getListenSd(), (struct sockaddr*)&address, &length);
    std::string adr = inet_ntoa(address.sin_addr);
    REQUIRE(adr == "0.0.0.0");

    acceptor.init();
    int val = getsockname(acceptor.getListenSd(), (struct sockaddr*)&address, &length);
    adr = inet_ntoa(address.sin_addr);
    REQUIRE(val == 0);
    REQUIRE(adr == "127.0.0.1");
}