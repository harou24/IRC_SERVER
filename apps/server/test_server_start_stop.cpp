#include "server.hpp"

#include <assert.h>
#include <unistd.h>

#include <iostream>
#include <thread>

Server serv(8080, "password", HOST);

void  runServer()
{
    std::cout << "Starting server...\n";
    serv.runOnce();
}

int main(void)
{
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
