#include "Server.hpp"

// Server::Server() : MultiClientHandler() {
//     acceptor = NULL;
//     isRunning = false;
// }

Server::Server(int port, std::string password) : MultiClientHandler(){
    acceptor = new TcpAcceptor(port, HOST);
    isRunning = false;
    clients.reserve(MAX_CLIENTS + 1);
    _mPassword = password;
}

Server::~Server(){
    clients.clear();
}

void            start(){
    // if (acceptor == NULL)
    //     exit(1);
    // acceptor.init();
    // MultiClientHandler::addFdToSet(acceptor.getListenSd());
}

// void            stop(){

// }

// void            stopSigHandler(int pid){

// }

// void            addClient(){

// }

// void            removeClient(){

// }