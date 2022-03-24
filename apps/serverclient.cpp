#include "TcpStream.hpp"
#include "TcpConnector.hpp"
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#define PORT 8080

int     main(void)
{
//    struct sockaddr_in  servaddr;
    // int                 sd;

    // sd = socket(AF_INET, SOCK_STREAM, 0);
    // servaddr.sin_family = AF_INET;
    // servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // servaddr.sin_port = htons(PORT);

    // std::cout << servaddr.sin_addr.s_addr << std::endl;
    // std::cout << servaddr.sin_port << std::endl;

    TcpConnector    test;

    TcpStream       *a = test.connect(PORT, "127.0.0.1");
    if (a){
        std::cout << a->getPeerIP() << std::endl;
        std::cout << a->getPeerPort() << std::endl;
    }

    return 0;
}
