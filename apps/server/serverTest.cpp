#include "Server.hpp"

#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#include <iostream>
#include <thread>

Server serv(8080, "password");

void  runServer()
{
    std::cout << "Starting server..." << serv.isRunning() << "\n";
    serv.start();
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
