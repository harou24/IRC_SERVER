#include "TcpConnector.hpp"

TcpStream*      TcpConnector::connect(int port, std::string server){
    struct sockaddr_in address;

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;//address family
    address.sin_port = htons(port);//converts host byte order to network byte order
    if (resolveHost(server, &address.sin_addr) != 0)//server contains IP
        address.sin_addr.s_addr = inet_addr(server.c_str());//convert IP to network byte order
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (::connect(sd, (struct sockaddr*)&address, sizeof(address)) != 0){
        throw std::runtime_error("connect " + std::string(strerror(errno)));
    }
    return new TcpStream(sd, &address);
}

int             TcpConnector::resolveHost(std::string host, struct in_addr* addr){
    struct addrinfo     *result;

    int res = getaddrinfo(host.c_str(), 0, 0, &result);//converts DNS name to IP addres in network byte order
    if (res == 0)//hostname is  valid DNS name
    {
        memcpy(addr, &((struct sockaddr_in *)result->ai_addr)->sin_addr, sizeof(struct in_addr));
        freeaddrinfo(result);
    }
    return res;
}