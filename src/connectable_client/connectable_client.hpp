#ifndef CONNECTABLE_CLIENT_HPP
# define CONNECTABLE_CLIENT_HPP

# include "client.hpp"

class ConnectableClient {

    public:
        ConnectableClient();
        ConnectableClient(const std::string& nick, TcpStream &stream);
        ~ConnectableClient();

        void    connect(int port, const std::string host);
        void    send(const std::string message);
        std::string receive();

    private:
        Client *cl;

};

#endif