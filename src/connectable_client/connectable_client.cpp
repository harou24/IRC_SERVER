#include "connectable_client.hpp"
#include <iostream>

ConnectableClient::ConnectableClient()
{ 
    _port = 8080;
    _host = "127.0.0.1";
    _client = new Client(_port, _host);
    _connector = new TcpConnector();
    _stream = NULL;
}

ConnectableClient::ConnectableClient(int port, std::string host)
{
    _port = port;
    _host = host;
    _client = new Client(port, host);
    _connector = new TcpConnector();
    _stream = NULL;
}

ConnectableClient::~ConnectableClient() { }

void    ConnectableClient::connect()
{
    try
    {
        _stream = _connector.connect(_port, _host);
    }
    catch(std::exception &e)
    {
        std::cout << e.what() << "\n";
    }
}

void    ConnectableClient::send(const std::string &message)
{
    _stream.send(message.c_str(), message.size());
    std::cout << "sent - " << message << std::endl;
}

std::string ConnectableClient::receive()
{
    int     length;
    char    line[256];

    length = _stream.receive(line, sizeof(line));
    line[length] = '\0';
    std::cout << "received - " << line << std::endl;
    return std::string(line);
}
