#include "TcpStream.hpp"

#include <assert.h>

int main(void)
{
//    int listenSd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
//    socklen_t length = sizeof(address);
    memset(&address, 0, sizeof(address));

    // int sd = ::accept(_mListenSd, (struct sockaddr*)&address, &length);
    TcpStream stream(0, &address);

    int nbSend = stream.send("Hello\n", 6);
    assert(nbSend == 6);
    char buffer[42];
    int nbRec = stream.receive(buffer, sizeof(buffer));
    buffer[nbRec] = '\0';
    std::cout << buffer << std::endl;

    return (0);
}