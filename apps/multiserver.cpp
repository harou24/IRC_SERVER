#include "server.hpp"
#include "TcpAcceptor.hpp"
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdexcept>
#include <cstdlib>
#include <cerrno>

#define PORT 8080

int         main(){
    server      a(8080, "127.0.0.1");
    TcpStream   *stream = NULL;

    a.start();
    while (1){
        stream = a.accept();
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
    return 0;
}