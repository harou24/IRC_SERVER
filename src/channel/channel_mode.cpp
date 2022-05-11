#include "channel_mode.hpp"

ChannelMode::ChannelMode() : opper_(0)
{
}

ChannelMode::~ChannelMode()
{
}

bool    ChannelMode::Invite() const
{
    std::cout << opper_ << std::endl;
    return (opper_ & (1<<1));
}

void    ChannelMode::removeInvite(const Client& cl)
{
    for(std::set<Client *>::iterator it = inventation_.begin(); it != inventation_.end(); it++)
    {
        if ((*it)->getNick() == cl.getNick())
        {
            this->inventation_.erase(it);
            return;
        }
    }
}

bool    ChannelMode::isInvite(const Client& cl)
{
    for(std::set<Client *>::iterator it = inventation_.begin(); it != inventation_.end(); it++)
    {
        if ((*it)->getNick() == cl.getNick())
            return true;
    }
    return false;
}

void    ChannelMode::addInvite(Client& cl)
{
    inventation_.insert(&cl);
}

void    ChannelMode::seton(char c, std::istringstream& ss)
{
    std::string word;
    switch (c)
    {
        case 'o': opper_ |= (1 << 0);
            break;
        case 'i': opper_ |= (1 << 1);
            break;
        case 't': opper_ |= (1 << 2);
            break;
        case 'n': opper_ |= (1 << 3);
            break;
        case 'l':
            if (ss>>word && atoi(word.c_str()) > 0)
            {
                opper_ |= (1 << 4);
                setClientLimit(atoi(word.c_str()));
            }
            else
                std::cout << "invalid size\n";
                // return;//eerrror
            break;
        case 'b':
            if (ss>>word && word.size() > 0)
                opper_ |= (1 << 5);
                //addword to banlist
            break;
        case 'k':
            if (ss>>word && word.size() > 0)
            {
                opper_ |= (1 << 6);
                setPassword(word);
            }       
            break;
        default:
            break;
    }
}

void    ChannelMode::setoff(char c, std::istringstream& ss)
{
    std::string word;
    switch (c)
    {
        case 'o': opper_ &= ~(1 << 0);
            break;
        case 'i': opper_ &= ~(1 << 1);
            break;
        case 't': opper_ &= ~(1 << 2);
            break;
        case 'n': opper_ &= ~(1 << 3);
            break;
        case 'l': opper_ &= ~(1 << 4);
            break;
        case 'b':
            if (ss>>word && word.size() > 0)
                opper_ &= ~(1 << 5);
                //remove word from banlist
            break;
        case 'k': opper_ &= ~(1 << 6);            
            break;
        default:
            break;
    }
}

void    ChannelMode::setMode(std::string str, std::string arg)
{
    std::istringstream  ss(arg);
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] == '-')
        {
            i++;
            while(i < str.length() && str[i] != '+')
                setoff(str[i++], ss);
        }
        if (i < str.length() && str[i] == '+')
        {
            i++;
            while(i < str.length() && str[i] != '-')
                seton(str[i++], ss);
        }
    }
}

char    ChannelMode::getModus() const
{
    return opper_;
}

int     ChannelMode::getClientLimit() const
{
    return clientLimit_;
}

void    ChannelMode::setClientLimit(int limit)
{
    clientLimit_ = limit;
}

std::string     ChannelMode::getPassword() const
{
    return password_;
}

void    ChannelMode::setPassword(std::string str)
{
    password_ = str;
}