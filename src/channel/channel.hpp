#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "client.hpp"
# include "replies.hpp"

/*
    opper(ator)_
    0 = o   4 = l
    1 = i   5 = b
    2 = t   6 = k
    3 = n   
*/

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
        bool                            isInvite(const Client& cl);
        bool                            Invite() const;
        void                            addInvite(Client& cl);
        void                            setMode(std::string str);
        void                            seton(char c);
        void                            setoff(char c);

        std::string                     getNames();
        std::set<Client *>::iterator    getClientByName(std::set<Client *>& set, std::string name) const;
        std::string                     getChannelName() const;

    private:

        std::string         name_;
        std::set<Client *>  clients_;
        std::set<Client *>  operators_;
        std::set<Client *>  inventation_;
        short               opper_;
};

#endif