#include "irc_server.hpp"

#include <iostream>
#include <string>

#include <limits.h>

int     main(int argc, char **argv)
{
    (void)argv;
    if (argc != 3)
    {
        std::cout << "usage: ./ircserv <port> <password>\n";
        exit(1);
    }

    int port = atoi(argv[1]);
    if (!(port > 1000 && port < INT_MAX))
    {
        std::cout << "The given port is not valide, it needs to be above 1000 and under MAX_INT\n";
        exit(1);
    }

    IrcServer   S(port, std::string(argv[2]));

    S.start();
    return 0;
}