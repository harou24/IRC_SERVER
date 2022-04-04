#include "TcpStream.hpp"

#include <assert.h>
#include <fcntl.h>
#include <cstring>

int main(void)
{
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));

    TcpStream stream(0, &address);

    int nbSend = stream.send("Give a world of 6letters\n", 26);
    assert(nbSend == 26);

    char buffer[420];
    int nbRec = stream.receive(buffer, sizeof(buffer));
    assert(nbRec == 7);
    return (0);
}