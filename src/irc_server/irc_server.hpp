#ifndef IRC_SERVER_HPP
# define IRC_SERVER_HPP

# include <vector>
# include <set>

# include "server.hpp"
# include "client.hpp"

class Client;

class IrcServer {

    public:
        IrcServer(int port, std::string password);
        ~IrcServer();

        void    start(void);
        void    stop(void);

        bool    isNickInUse(const std::string &nickname);
        Client* getClientByStream(TcpStream *stream);
        Client* getClientByName(std::string name);

        void    addClient(Client* cl);
        void    removeClient(Client *cl);

        bool    isChannel(std::string channel);
        bool    isInChannel(std::string channel, std::string nick);
        void    addChannel(std::string channel);
        void    addInChannel(std::string channel, std::string nick);
        void    removeInChannel(std::string channel, std::string nick);
        
        std::set<std::string>&   getChannel(std::string channel);
        

        bool    isRunning(void) const;
        
    private:
        Server                                          *_mServer;
        int                                             _mNbclients;
        std::vector<Client *>                           clients_;
        std::map<std::string, std::set<std::string> >   channel_;
    
        IrcServer(const IrcServer &server);
        IrcServer();
};

#endif

