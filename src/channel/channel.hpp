#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "channel_mode.hpp"

class Client;
class channel_mode;

class Channel
{
    public:
        Channel();
        Channel(std::string name, Client& cl);
        ~Channel();

        void                            addClient(Client& cl);
        void                            removeClient(Client& cl, std::string reply);
        void                            addOperator(Client &cl);
        void                            removeOperator(Client &cl);

        void                            sendMessage(Client& cl, std::string msg);

        bool                            isInChannel(std::string nick);
        bool                            isOperator(Client& cl);
        bool                            isActive() const;
        channel_mode&                   getMode() const;

        std::string                     getNames();
        std::set<Client *>::iterator    getClientByName(std::set<Client *>& set, std::string name) const;
        std::string                     getChannelName() const;

    private:
        std::string         name_;
        std::set<Client *>  clients_;
        std::set<Client *>  operators_;
        channel_mode        *mode_;
};

#endif