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
        int             port_;
        std::string     host_;
        Client*         client_;
        TcpConnector*   connector_;
        TcpStream*      stream_;
};

#endif