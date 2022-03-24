#include "TcpStream.hpp"
#include "TcpConnector.hpp"
#include "TcpAcceptor.hpp"
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdexcept>

#define PORT 8080

int     main(void)
{
    TcpAcceptor     server(PORT, "127.0.0.1");
    TcpStream       *stream = NULL;

    try{
        server.start();
    }
    catch(std::exception &e){
        std::cout << e.what() << std::endl;
        std::cout << std::strerror(errno) << std::endl;
        return 0;
    }
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
            std::cout << e.what() << std::endl;
            std::cout << std::strerror(errno) << std::endl;
            return 0;
        }
    }
    return 0;
}
