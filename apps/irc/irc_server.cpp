#include "irc_server.hpp"

#include <iostream>
#include <string>

int     main(int argc, char **argv)
{
    (void)argv;
    if (argc != 3)
    {
        std::cout << "usage: ./ircserv <port> <password>\n";
        exit(1);
    }

    IrcServer   S(atoi(argv[1]), std::string(argv[2]));

    S.start();
    return 0;
}