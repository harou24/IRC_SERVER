#include "irc_server.hpp"
#include "connectable_client.hpp"

#include <string>
#include <iostream>
#include <thread>

#include <assert.h>

IrcServer g_server(8080, "");

ConnectableClient g_client(8080, std::string(HOST));
ConnectableClient g_client_2(8080, std::string(HOST));


void    serverJob()
{
    g_server.start();
}

void    topicJob()
{
    assert(g_server.isRunning());
    g_client.connect("User1");

    g_client.send("CAP LS\nNICK User1\nUSER usr usr usr :usr\n");
    sleep(1);
    std::string response = g_client.receive();
    assert(!response.empty());
    std::cout << response << "\n";

    g_client.send("TOPIC\n");
    sleep(1);
    response = g_client.receive();
    assert(!response.empty());
    std::cout << response << "\n";

    g_client.send("JOIN #channel\n");
    sleep(1);
    response = g_client.receive();
    assert(!response.empty());
    std::cout << response << "\n";

    g_client.send("TOPIC #channel :testTopictest\n");
    sleep(1);
    response = g_client.receive();
    assert(!response.empty());
    std::cout << response << "\n";

    Topic topic = g_server.getChannel("#channel").getMode().getTopic();
    assert(topic.topic == ":testTopictest");
    assert(topic.topic_nick == "User1");

    g_client_2.connect("User2");
    g_client_2.send("CAP LS\nNICK User2\nUSER usr2 usr2 usr2 :usr2\n");
    sleep(1);
    response = g_client_2.receive();
    assert(!response.empty());
    std::cout << response << "\n";

    g_client_2.send("TOPIC #channel\n");
    sleep(1);
    response = g_client_2.receive();
    assert(!response.empty());
    std::cout << response << "\n";

    g_client_2.send("TOPIC #channel :not possible\n");
    sleep(1);
    response = g_client_2.receive();
    assert(!response.empty());
    std::cout << response << "\n";

    g_client_2.send("JOIN #channel\n");
    sleep(1);
    response = g_client_2.receive();
    assert(!response.empty());
    std::cout << response << "\n";

    g_client.send("MODE #channel +t\n");
    sleep(1);
    response = g_client.receive();
    assert(!response.empty());
    std::cout << response << "\n";

    g_client_2.send("TOPIC #channel :invalid\n");
    sleep(1);
    response = g_client_2.receive();
    assert(!response.empty());
    std::cout << response << "\n";

    topic = g_server.getChannel("#channel").getMode().getTopic();
    assert(topic.topic != ":invalid");

    g_client.send("MODE #channel -t\n");
    sleep(1);
    response = g_client.receive();
    assert(!response.empty());
    std::cout << response << "\n";

    g_client_2.send("TOPIC #channel :valid\n");
    sleep(1);
    response = g_client_2.receive();
    assert(!response.empty());
    std::cout << response << "\n";

    topic = g_server.getChannel("#channel").getMode().getTopic();
    assert(topic.topic == ":valid");
    assert(topic.topic_nick == "User2");
}

int     main(void)
{
    std::thread server_thread(serverJob);
    sleep(3);

    std::thread client_thread(topicJob);

    client_thread.join();

    g_server.stop();
    assert(g_server.isRunning() == false);
    server_thread.join();

    return (0);
}