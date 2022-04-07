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

void    validArguments(int argc) {
    if (argc != 3)
    {
        std::cout << "usage: client <port> <ip-addres>\n";
        exit(1);
    }
}

void    printException(std::exception &e) {
    std::cout << e.what() << std::endl;
    exit(1);
}

void    send(std::string message, TcpStream &stream) {
    stream.send(message.c_str(), message.size());
    std::cout << "sent - " << message << std::endl;
}

void    receive(TcpStream &stream) {
    int     length;
    char    line[256];

    length = stream.receive(line, sizeof(line));
    line[length] = '\0';
    std::cout << "received - " << line << std::endl;
}

void    basicTest(TcpConnector &connector, char **argv, std::string message) {
    try
    {
        TcpStream* stream = connector.connect(atoi(argv[1]), argv[2]);
        if (stream) {
            send(message, *stream);
            receive(*stream);
            delete stream;
        }
    }
    catch(std::exception &e)
    {
        printException(e);
    }
}

int main(int argc, char **argv) {
    validArguments(argc);

    std::string message;
    TcpConnector* connector = new TcpConnector();

    basicTest(*connector, argv, "Is there life on Mars?");
    basicTest(*connector, argv, "Why is there air?");

    delete connector;
    return 0;
}