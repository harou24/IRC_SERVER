#include "TcpStream.hpp"
#include "Server.hpp"
#include "TcpAcceptor.hpp"
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdexcept>
#include <cstdlib>
#include <cerrno>

int         main(){
    Server      s(8080, "lalala");
    return 0;
}