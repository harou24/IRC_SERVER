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

void testChannel()
{
    assert(g_server.isRunning());

    //connecting two users to the server
    g_client.connect("User1");
    g_client.send("CAP LS\nNICK User1\nUSER usr usr usr :usr\n");
    sleep(1);

    g_client_2.connect("User2");
    g_client_2.send("CAP LS\nNICK User2\nUSER usr2 usr2 usr2 :usr2\n");
    assert(g_client_2.getClient().getNick() == "User2");
    sleep(1);

    //User2 joins the channel first, so should be operator...
    g_client_2.send("JOIN #channel\n");
    sleep(1);
    std::string response = g_client_2.receive();
    assert(g_server.getChannel("#channel").isActive() == true);
    assert(g_server.getChannel("#channel").isInChannel("User2") == true);
    //The following assertion fails
    assert(g_server.getChannel("#channel").isOperator(g_client_2.getClient()) == true);

    g_client.send("JOIN #channel\n");
    assert(g_server.getChannel("#channel").isInChannel("User1") == true);
    assert(g_server.getChannel("#channel").isInChannel("User2") == true);
    assert(g_server.getChannel("#channel").isOperator(g_client_2.getClient()) == true);
}

int main(void)
{
    std::thread server_thread(serverJob);
    sleep(3);

    std::thread channel_thread(testChannel);

    channel_thread.join();

    g_server.stop();
    assert(g_server.isRunning() == false);
    server_thread.join();

    return (0);
}