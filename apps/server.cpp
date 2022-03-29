#include "TcpStream.hpp"
#include "TcpConnector.hpp"
#include "TcpAcceptor.hpp"
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdexcept>
#include <cstdlib>
#include <cerrno>

#define PORT 8080

void    validArguments(int argc){
    if (argc != 3){
        std::cout << "usage: server <port> <ip-addres>\n";
        exit(1);
    }
}

void    printException(std::exception &e){
    std::cout << e.what() << std::endl;
    std::cout << std::strerror(errno) << std::endl;
    exit(1);
}

void    setupServer(TcpAcceptor &server){
    try{
        server.init();
    }
    catch(std::exception &e){
        printException(e);
    }
}

int     main(int argc, char **argv)
{
    validArguments(argc);

    TcpAcceptor     server(atoi(argv[1]), argv[2]);
    TcpStream       *stream = NULL;

    setupServer(server);
    while (1){
        try{
            stream = server.accept();
            if (stream){
                size_t          len;
                char     buffer[256];
                while ((len = stream->receive(buffer, sizeof(buffer))) > 0){
                    buffer[len] = '\0';
                    std::cout << "received: " << buffer << std::endl;
                    stream->send(buffer, len);
                }
                delete stream;
            }
        }
        catch(std::exception &e){
            printException(e);
        }
    }
    return 0;
}
