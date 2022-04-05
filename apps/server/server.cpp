#include "TcpStream.hpp"
#include "Server.hpp"
#include "TcpAcceptor.hpp"
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdexcept>
#include <cstdlib>
#include <cerrno>
#include <csignal>

void            stopSigHandler(int pid){
    std::cout << "Stopping the server.... signal pid = " << pid << std::endl;
    exit(1);
}

void            SetupSignals(){
    signal(SIGQUIT, stopSigHandler);
    signal(SIGINT, stopSigHandler);
}

int         main(){
    Server      s(8080, "lalala");

    SetupSignals();
    s.runOnce();
    try{
           s.start();
           while (!s.getQueue().empty()){
               std::cout << "Message = " << s.getQueue().front().data << std::endl;
               std::cout << *(s.getQueue().front().stream) << std::endl;
               s.getQueue().pop();
           }
    }
    catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}