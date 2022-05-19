#include "irc_server.hpp"
#include "connectable_client.hpp"

#include <string>
#include <iostream>
#include <thread>

#include <assert.h>


IrcServer g_server(8080, "");

void serverJob()
{
    g_server.start();
}

void connectClients(void)
{

        ConnectableClient client(8080, std::string(HOST));
        client.connect("user1");
        sleep(1);
        client.send("CAP LS\nNICK User1\nUSER user user user :user\n");
        sleep(1);
        std::string response = client.receive();
        assert(!response.empty());

        ConnectableClient client2(8080, std::string(HOST));
        client2.connect("user2");
        sleep(1);
        client2.send("CAP LS\nNICK User2\nUSER user2 user2 user2 :user2\n");
        sleep(1);
        response = client2.receive();
        assert(!response.empty());


        ConnectableClient client3(8080, std::string(HOST));
        client3.connect("user3");
        sleep(1);
        client3.send("CAP LS\nNICK user3\nUSER user3 user3 user3 :user3\n");
        sleep(1);
        response = client3.receive();
        assert(!response.empty());

        ConnectableClient client4(8080, std::string(HOST));
        client4.connect("user4");
        sleep(1);
        client4.send("CAP LS\nNICK user4\nUSER user4 user4 user4 :user4\n");
        sleep(1);
        response = client4.receive();
        assert(!response.empty());

        ConnectableClient client5(8080, std::string(HOST));
        client5.connect("user5");
        sleep(1);
        client5.send("CAP LS\nNICK user5\nUSER user5 user5 user5 :user5\n");
        sleep(1);
        response = client5.receive();
        assert(!response.empty());

        //trying to connect client 6 but the MAX is 5
        ConnectableClient client6(8080, std::string(HOST));
        client6.connect("user6");
        sleep(1);
        client6.send("CAP LS\nNICK user6\nUSER user6 user6 user6 :user6\n");

}

int main(void)
{
    std::thread server_thread(serverJob);
    sleep(3);
    assert(g_server.isRunning());


    connectClients();
    assert(g_server.getNbClients() == 5);

    g_server.stop();
    sleep(1); 
    assert(g_server.isRunning() == false);
    server_thread.join();

    return (0);
}