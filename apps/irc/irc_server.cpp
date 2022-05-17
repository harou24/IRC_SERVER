#include "irc_server.hpp"

#include <iostream>
#include <string>

#define MAX_PORT_NB 65536

int     main(int argc, char **argv)
{
    (void)argv;
    if (argc != 3)
    {
        std::cout << "usage: ./ircserv <port> <password>\n";
        exit(1);
    }

    int port = atoi(argv[1]);
    if (!(port > 1000 && port < MAX_PORT_NB))
    {
        std::cout << "The given port is not valide, it needs to be above 1000 and under 65536\n";
        exit(1);
    }

    IrcServer   S(port, std::string(argv[2]));

    S.start();
    return 0;
}
