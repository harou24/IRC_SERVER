#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "channel_mode.hpp"

class Client;
class ChannelMode;

class Channel
{
    public:
        Channel();
        Channel(std::string name, Client& cl, unsigned int time);
        ~Channel();

        void                            addClient(Client& cl);
        void                            removeClient(Client& cl, std::string reply);
        void                            addOperator(Client &cl);
        void                            removeOperator(Client &cl);

        void                            sendMessage(Client& cl, std::string msg);

        bool                            isInChannel(std::string nick);
        bool                            isOperator(Client& cl);
        bool                            isActive() const;
        ChannelMode&                    getMode() const;

        std::string                     getNames();
        std::set<Client *>::iterator    getClientByName(std::set<Client *>& set, std::string name) const;
        std::string                     getChannelName() const;

        int                             NbrClients() const;
        unsigned int                    getCreationTime() const;


    private:
        std::string         name_;
        std::set<Client *>  clients_;
        std::set<Client *>  operators_;
        ChannelMode*        mode_;
        unsigned int        creationTime_;
};

#endif