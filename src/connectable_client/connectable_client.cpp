#include "connectable_client.hpp"

void    ConnectableClient::send(const std::string message){
    _mStream.send(message.c_str(), message.size());
    #if 1
        print("DEBUG", "sent - " + message);
    #endif
}

std::string ConnectableClient::receive(){
    int     length;
    char    line[256];

    length = _mStream.receive(line, sizeof(line));
    line[length] = '\0';
    #if 1
        print("DEBUG", "received - " + line);
    #endif
    return std::string(line);
}

void    ConnectableClient::connect(int port, std::string host){
    TcpConnector connector;

    try {
        _mStream = connector.connect(port, host);
    }
    catch(std::exception &e){
        print("ERROR", e.what());
        // std::cout << e.what() << "\n";
    }
}
