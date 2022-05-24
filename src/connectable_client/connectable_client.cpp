#include "connectable_client.hpp"
#include <iostream>

#define MAX_RECEIVE 2048


ConnectableClient::ConnectableClient()
{ 
    port_ = 8080;
    host_ = std::string(HOST);
    connector_ = new TcpConnector();
    client_ = NULL;
}

ConnectableClient::ConnectableClient(int port, std::string host)
{
    port_ = port;
    host_ = host;
    connector_ = new TcpConnector();
    client_ = NULL;
}

ConnectableClient::~ConnectableClient()
{
    delete stream_;
    delete client_;
    delete connector_;
}

void    ConnectableClient::connect(const std::string &nick)
{
    try
    {
        stream_ = connector_->connect(port_, host_);
    }
    catch(std::exception &e)
    {
        print("ERROR", e.what());
    }
    client_ = new Client(nick, stream_);
}

void    ConnectableClient::send(const std::string &message)
{
    stream_->send(message.c_str(), message.size());
    print("DEBUG", "send " + message);
}

std::string ConnectableClient::receive()
{
    int     length;
    char    data[MAX_RECEIVE];

    length = stream_->receive(data, sizeof(data));
    data[length] = '\0';
    return std::string(data);
}

Client& ConnectableClient::getClient() { return *client_; }
