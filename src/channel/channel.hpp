#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "client.hpp"

class Client;

class Channel
{
    public:
        Channel();
        Channel(std::string name, Client& cl);
        ~Channel();

        void                addClient(Client& cl);
        void                removeClient(Client& cl);
        void                addOperator(Client &cl);
        void                removeOperator(Client &cl);

        bool                isInChannel(std::string nick);

        bool                isOperator(Client& cl) const;
        bool                isActive() const;

        std::string         getNames();

        void                sendMessage(Client& cl, std::string msg);
        std::set<Client *>::iterator    getClientByName(std::set<Client *>& set, std::string name);

    private:

        std::string         name_;
        std::set<Client *>  clients_;
        std::set<Client *>  operators_;

};

#endif