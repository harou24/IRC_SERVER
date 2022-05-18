#ifndef CONNECTABLE_CLIENT_HPP
# define CONNECTABLE_CLIENT_HPP

# include "client.hpp"
# include "tcp_connector.hpp"

# include <string>

class ConnectableClient {

    public:
        ConnectableClient();
        ConnectableClient(int port, std::string host);
        ~ConnectableClient();

        void    connect(const std::string &nick);
        void    send(const std::string &message);
        std::string receive();

        Client& getClient();

    private:
        int             _port;
        std::string     _host;
        Client*         _client;
        TcpConnector*   _connector;
        TcpStream*      _stream;
};

#endif