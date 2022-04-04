#include "Server.hpp"

#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#include <iostream>

int main(void)
{
    Server serv(8080, "password");
    assert(serv.getPassword() == "password");

    pid_t servPid = fork();
    if (servPid == 0)
    {
        serv.start();
    }
    else
    {
        sleep(2);
        std::cout << "Running->" << serv.isRunning() << "\n";
        assert(serv.isRunning() == false);
        kill(servPid, SIGKILL);
    }
    return 0;   
}


/*
SCENARIO("start and stop server")
{
    GIVEN("construct server")
    {
        Server serv(8080, "");

        THEN("serv should not be running...")
        {
            REQUIRE(serv.getPassword() == "");
            REQUIRE(serv.isRunning() == false);
            REQUIRE(serv.getQueue().size() == 0);
            REQUIRE(serv.getClients().size() == 0);
        }
        WHEN("Server starts in a new process...")
        {
            pid_t servPid = fork();
            if (servPid == 0)
                serv.start();

            THEN("Server should be running...")
            {
                sleep(3);
                REQUIRE(serv.isRunning() == true);
                kill(servPid, SIGKILL);
            }

        }
    }
}
*/