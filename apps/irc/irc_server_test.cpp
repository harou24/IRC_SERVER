#include "irc_server.hpp"
#include "connectable_client.hpp"
#include <string>

IrcServer g_server(8080, "");
ConnectableClient g_client();

void serverJob()
{
    g_server.start();
}

void clientJob()
{
    g_client.send("HELLO\n");
}

int main(void)
{
    return (0);
}