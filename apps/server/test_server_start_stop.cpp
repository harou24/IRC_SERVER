#include "Server.hpp"

#include <iostream>
#include <thread>

#include <assert.h>
#include <unistd.h>

Server serv(8080, "password");

void  runServer() {
    std::cout << "Starting server...\n";
    serv.runOnce();
}

int main() {
    assert(serv.getPassword() == "password");

    std::thread serverJob(runServer);
    sleep(1);
    assert(serv.isRunning() == true);

    std::cout << "Stopping server..." << "\n";
    serv.stop();
    assert(serv.isRunning() == false);

    serverJob.join();
    return 0;
}
