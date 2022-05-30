#ifndef IRC_SERVER_HPP
# define IRC_SERVER_HPP

# include <set>

# include "server.hpp"
# include "channel.hpp"

# include <cctype>

# define TIMEOUT 120

class Client;
class Channel;

class IrcServer {

    typedef std::set<std::pair<Client *, unsigned int> >    Waitlist;

    public:
        IrcServer(int port, std::string password, std::string host);
        ~IrcServer();

        void                                start(void);
        void                                stop(void);

        bool                                isNickInUse(const std::string &nickname);
        Client*                             getClientByStream(TcpStream *stream) const;
        Client*                             getClientWaitlistByStream(TcpStream *stream) const;
        Client*                             getClientByName(std::string name) const;

        void                                addClient(Client* cl);
        void                                addClientToWaitlist(Client* cl);
        void                                ConnectClient(Client* cl);
        void                                removeClientWaitlist(Client* cl);
        void                                removeClient(Client* cl, std::string reply);
        void                                removeStream(TcpStream *stream);

        bool                                isChannel(std::string channel);
        void                                addChannel(std::string channel, Client& cl, unsigned int time);
        void                                removeChannel(std::string channel);
        Channel&                            getChannel(std::string channel);
        
        bool                                isRunning(void) const;

        bool                                isPasswordOk(const std::string &password) const;
        size_t                              getNbClients(void) const;
        void                                disconnect(int fd);

        void                                sendPing();
        void                                WaitlistCheck();
        
    private:
        Server*                         server_;
        Waitlist                        clientsWaitlist_;
        std::set<Client *>              clients_;
        std::map<std::string, Channel*> channels_;
    
        IrcServer();
};

#endif