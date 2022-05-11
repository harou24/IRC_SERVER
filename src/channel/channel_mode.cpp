#include "channel_mode.hpp"

channel_mode::channel_mode() : opper_(0)
{
}

channel_mode::~channel_mode()
{
}

bool    channel_mode::Invite() const
{
    std::cout << opper_ << std::endl;
    return (opper_ & (1<<1));
}

bool    channel_mode::isInvite(const Client& cl)
{
    for(std::set<Client *>::iterator it = inventation_.begin(); it != inventation_.end(); it++)
    {
        if ((*it)->getNick() == cl.getNick())
        {
            this->inventation_.erase(it);
            return true;
        }
    }
    return false;
}

void    channel_mode::addInvite(Client& cl)
{
    inventation_.insert(&cl);
}

void    channel_mode::seton(char c)
{
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
        case 'l': opper_ |= (1 << 4);
            break;
        case 'b': opper_ |= (1 << 5);
            break;
        case 'k': opper_ |= (1 << 6);            
            break;
        default:
            break;
    }
}

void    channel_mode::setoff(char c)
{
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
        case 'b': opper_ &= ~(1 << 5);
            break;
        case 'k': opper_ &= ~(1 << 6);            
            break;
        default:
            break;
    }
}

void    channel_mode::setMode(std::string str)
{
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] == '-')
        {
            i++;
            while(i < str.length() && str[i] != '+')
                setoff(str[i++]);
        }
        if (i < str.length() && str[i] == '+')
        {
            i++;
            while(i < str.length() && str[i] != '-')
                seton(str[i++]);
        }
    }
}