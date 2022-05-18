#include "connectable_client.hpp"
#include <iostream>

#define MAX_RECEIVE 2048


ConnectableClient::ConnectableClient()
{ 
    _port = 8080;
    _host = std::string(HOST);
    _connector = new TcpConnector();
    _client = NULL;
}

ConnectableClient::ConnectableClient(int port, std::string host)
{
    _port = port;
    _host = host;
    _connector = new TcpConnector();
    _client = NULL;
}

ConnectableClient::~ConnectableClient()
{
    delete _stream;
    delete _client;
    delete _connector;
}

void    ConnectableClient::connect(const std::string &nick)
{
    try
    {
        _stream = _connector->connect(_port, _host);
    }
    catch(std::exception &e)
    {
        std::cout << e.what() << "\n";
    }
    _client = new Client(nick, _stream);
}

void    ConnectableClient::send(const std::string &message)
{
    _stream->send(message.c_str(), message.size());
    std::cout << "sent - " << message << std::endl;
}

std::string ConnectableClient::receive()
{
    int     length;
    char    data[MAX_RECEIVE];

    length = _stream->receive(data, sizeof(data));
    data[length] = '\0';
    return std::string(data);
}

Client& ConnectableClient::getClient() { return *_client; }
