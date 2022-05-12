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

class ChannelMode
{
    public:
        ChannelMode();
        ~ChannelMode();

        void        setChan(std::string name);

        bool        isInvite(const Client& cl);
        void        removeInvite(const Client& cl);
        bool        Invite() const;
        void        addInvite(Client& cl);
        void        setMode(std::string str, std::string arg, Client& cl, std::string& reply);
        void        seton(char c, std::istringstream& ss, Client& cl, std::string& reply);
        void        setoff(char c, std::istringstream& ss);
        char        getModus() const;

        int         getClientLimit() const;
        void        setClientLimit(int limit);
        
        void        setBan(std::string name);
        std::string getBan(std::string nick, std::string& reply);
        

        std::string getPassword() const;
        void        setPassword(std::string str);

    private:
        std::set<Client *>                              inventation_;
        char                                            opper_;
        int                                             clientLimit_;
        std::string                                     password_;
        std::string                                     channel_;
        std::set<std::pair<std::string, unsigned int> > banList_;
};


#endif