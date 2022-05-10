#include "irc_server.hpp"
#include "connectable_client.hpp"

#include <string>
#include <iostream>
#include <thread>

#include <assert.h>

IrcServer g_server(8080, "");

ConnectableClient g_client(8080, "127.0.0.1");
ConnectableClient g_client_2(8080, "127.0.0.1");


void serverJob()
{
    g_server.start();
}

void clientJob()
{
    assert(g_server.isRunning());
    g_client.connect("User1");

    g_client.send("CAP LS\nNICK User1\nUSER usr usr usr :usr\n");
    sleep(1);
    std::string response = g_client.receive();
    assert(!response.empty());
    std::cout << response << "\n";

}

void clientJob2()
{
    assert(g_server.isRunning());
    g_client_2.connect("User2");

    g_client_2.send("CAP LS\nNICK User2\nUSER usr2 usr2 usr2 :usr2\n");
    sleep(1);
    std::string response = g_client_2.receive();
    assert(!response.empty());
    std::cout << response << "\n";

    g_client_2.send("PRIVMSG NonExistingNick :hello\n");
    sleep(1);
    response = g_client_2.receive();
    assert(response == ":127.0.0.1 401 User2 NonExistingNick :No such nick/channel\n");

}

int main(void)
{
    std::thread server_thread(serverJob);
    sleep(3);

    std::thread client_thread(clientJob);
    std::thread client_thread_2(clientJob2);

    client_thread.join();
    client_thread_2.join();

    g_server.stop();
    assert(g_server.isRunning() == false);
    server_thread.join();

    return (0);
}