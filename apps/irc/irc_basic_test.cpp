#include "irc_server.hpp"
#include "connectable_client.hpp"

#include <string>
#include <iostream>
#include <thread>

#include <assert.h>

IrcServer g_server(8080, "");
ConnectableClient g_client(8080, std::string(HOST));

void serverJob()
{
    g_server.start();
}

void clientJob()
{
    assert(g_server.isRunning());
    g_client.connect("Test");

    g_client.send("CAP LS\nNICK Test\nUSER usr usr usr :usr\n");
    sleep(1);
    std::string response = g_client.receive();
    assert(!response.empty());
    std::cout << response << "\n";


    g_client.send("NICK harou\n");
    sleep(1);
    response = g_client.receive();
    assert(!response.empty() && response == ":Test NICK harou\n");
    std::cout << response << "\n";


    g_client.send("NICK nickTooLongToBeValid...\n");
    sleep(1);
    response = g_client.receive();
    assert(!response.empty() && response == ":nickTooLongToBeValid... Error nickname is not valid\n");
    std::cout << response << "\n";

    g_client.send("AWAY :I'm back in 20min\n");
    sleep(1);
    response = g_client.receive();
    assert(!response.empty() && response == ":" + std::string(HOST) + " 306 :You have been marked as being away\n");
    std::cout << response << "\n";

    g_client.send("AWAY\n");
    sleep(1);
    response = g_client.receive();
    assert(!response.empty() && response == ":" + std::string(HOST) + " 305 :You are no longer marked as being away\n");
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