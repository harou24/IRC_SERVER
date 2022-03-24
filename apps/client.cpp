#include "TcpStream.hpp"
#include "TcpConnector.hpp"
#include "TcpAcceptor.hpp"
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdexcept>

#define PORT 8080

using namespace std;

int main()
{
    int len;
    string message;
    char line[256];
    // std::string line;
    TcpConnector* connector = new TcpConnector();
    try{
        TcpStream* stream = connector->connect(8080, "127.0.0.1");
        if (stream) {
            message = "Is there life on Mars?";
            stream->send(message.c_str(), message.size());
            printf("sentA - %s\n", message.c_str());
            len = stream->receive(line, sizeof(line));
            line[len] = '\0';
            printf("receivedA - %s\n", line);
            delete stream;
        }
    }
    catch(std::exception &e){
        std::cout << std::strerror(errno) << std::endl;
        // std::cout << e.what() << std::endl;
    }

    try{
        TcpStream* stream2 = connector->connect(8080, "127.0.0.1");
        if (stream2) {
            message = "Why is there air?";
            stream2->send(message.c_str(), message.size());
            printf("sentB - %s\n", message.c_str());
            len = stream2->receive(line, sizeof(line));
            line[len] = '\0';
            printf("receivedB - %s\n", line);
            delete stream2;
        }
    }
    catch(std::exception &e){
        std::cout << std::strerror(errno) << std::endl;
        // std::cout << e.what() << std::endl;
    }
    delete connector;
    exit(0);
}