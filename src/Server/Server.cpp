#include "Server.hpp"

// Server::Server() : MultiClientHandler() {
//     isRunning = false;
// }

Server::Server(int port, std::string password) : MultiClientHandler(), acceptor(port, HOST){
    isRunning = false;
    clients.reserve(MAX_CLIENTS + 1);
    _mPassword = password;
}

Server::~Server(){
    clients.clear();
}

void            Server::start(){
    acceptor.init();
    MultiClientHandler::addFdToSet(5);
}

// void            stop(){

// }

// void            stopSigHandler(int pid){

// }

// void            addClient(){

// }

// void            removeClient(){

// }