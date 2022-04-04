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
    std::queue<Message>     q;

    SetupSignals();
    try{
        while(1){
           s.start();
           q = s.getQueue();
           std::cout << "~~~~~~~~~~~~~\n";
           while (!q.empty()){
               std::cout << "Message = " << q.front().data << std::endl;
               std::cout << *(q.front().stream) << std::endl;
               q.pop();
           }
        }
    }
    catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}