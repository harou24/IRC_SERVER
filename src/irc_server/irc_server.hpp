#ifndef IRC_SERVER_HPP
# define IRC_SERVER_HPP

# include <vector>
# include <set>

# include "server.hpp"
# include "channel.hpp"

class Client;
class Channel;

class IrcServer {

    public:
        IrcServer(int port, std::string password);
        ~IrcServer();

        void                                start(void);
        void                                stop(void);

        bool                                isNickInUse(const std::string &nickname);
        Client*                             getClientByStream(TcpStream *stream) const;
        Client*                             getClientWaitListByStream(TcpStream *stream) const;
        Client*                             getClientByName(std::string name) const;

        void                                addClient(Client* cl);
        void                                addClientToWaitList(Client* cl);
        void                                ConnectClient(Client* cl);
        void                                removeClientWaitList(Client* cl);
        void                                removeClient(Client* cl, std::string reply);
        void                                removeStream(TcpStream *stream);

        bool                                isChannel(std::string channel);
        void                                addChannel(std::string channel, Client& cl, unsigned int time);
        void                                removeChannel(std::string channel);
        Channel&                            getChannel(std::string channel);
        std::map<std::string, Channel*>&    getAllChannels();
        
        bool                                isRunning(void) const;

        bool                                isPasswordOk(const std::string &password) const;
        size_t                              getNbClients(void) const;
        void                                disconnect(int fd);

        void                                sendPing();
        
    private:
        Server*                         server_;
        std::vector<Client *>           clientsWaitList_;
        std::vector<Client *>           clients_;
        std::map<std::string, Channel*> channels_;
    
        IrcServer();
};

#endif

