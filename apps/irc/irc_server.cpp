#include "irc_server.hpp"

#include <iostream>
#include <string>
#include "colors.h"
#include <iomanip>

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
    char buffer[256];
    gethostname(buffer, sizeof(buffer));

    std::cout << PURPLE << "IRCSERVER is running\nOn port: " << port << "\nHosted by: " << buffer << RESET << "\n";
    if (std::string(argv[2]).length() > 0)
        std::cout << PURPLE << "The password is: " << argv[2] << RESET << std::endl;
    IrcServer   S(port, std::string(argv[2]), buffer);

    S.start();
    return 0;
}
