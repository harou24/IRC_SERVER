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
        void                            removeClient(Client& cl, std::string reply);
        void                            addOperator(Client &cl);
        void                            removeOperator(Client &cl);

        void                            sendMessage(Client& cl, std::string msg);

        bool                            isInChannel(std::string nick);
        bool                            isOperator(Client& cl);
        bool                            isActive() const;
        bool                            isInvite() const;

        std::string                     getNames();
        std::set<Client *>::iterator    getClientByName(std::set<Client *>& set, std::string name) const;

    private:

        std::string         name_;
        std::set<Client *>  clients_;
        std::set<Client *>  operators_;
        bool                Invite_;

};

#endif