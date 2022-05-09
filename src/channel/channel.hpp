#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "client.hpp"
# include "replies.hpp"

class Client;

class Channel
{
    public:
        Channel();
        Channel(std::string name, Client& cl);
        ~Channel();

        void                            addClient(Client& cl);
        void                            removeClient(Client& cl);
        void                            addOperator(Client &cl);
        void                            removeOperator(Client &cl);

        void                            sendMessage(Client& cl, std::string msg);

        bool                            isInChannel(std::string nick);
        bool                            isOperator(Client& cl) const;
        bool                            isActive() const;

        std::string                     getNames() const;
        std::set<Client *>::iterator    getClientByName(std::set<Client *>& set, std::string name) const;

    private:

        std::string         name_;
        std::set<Client *>  clients_;
        std::set<Client *>  operators_;

};

#endif