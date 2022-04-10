#include "connectable_client.hpp"

void    ConnectableClient::send(const std::string message){
    _mStream.send(message.c_str(), message.size());
    std::cout << "sent - " << message << std::endl;
}

std::string ConnectableClient::receive(){
    int     length;
    char    line[256];

    length = _mStream.receive(line, sizeof(line));
    line[length] = '\0';
    std::cout << "received - " << line << std::endl;
    return std::string(line);
}

void    ConnectableClient::connect(int port, std::string host){
    TcpConnector connector;

    try {
        _mStream = connector.connect(port, host);
    }
    catch(std::exception &e){
        std::cout << e.what() << "\n";
    }
}
