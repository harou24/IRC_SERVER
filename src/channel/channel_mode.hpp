#ifndef CHANNEL_MODE_HPP
# define CHANNEL_MODE_HPP

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

class channel_mode
{
    public:
        channel_mode();
        ~channel_mode();

        bool    isInvite(const Client& cl);
        bool    Invite() const;
        void    addInvite(Client& cl);
        void    setMode(std::string str);
        void    seton(char c);
        void    setoff(char c);

    private:
        std::set<Client *>  inventation_;
        char                opper_;
};


#endif