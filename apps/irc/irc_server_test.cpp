#include "irc_server.hpp"
#include "connectable_client.hpp"

#include <string>
#include <iostream>
#include <thread>

#include <assert.h>

IrcServer g_server(8080, "");
ConnectableClient g_client(8080, "127.0.0.1");

void serverJob()
{
    g_server.start();
}

void clientJob()
{
    assert(g_server.isRunning());
    g_client.connect();
    g_client.send("NICK Test\n");
    sleep(1);
    std::string response = g_client.receive();
    assert(!response.empty());
    std::cout << response << "\n";
}

int main(void)
{
    std::thread server_thread(serverJob);
    sleep(3);
    std::thread client_thread(clientJob);
    client_thread.join();
    g_server.stop();
    assert(g_server.isRunning() == false);
    server_thread.join();
    return (0);
}