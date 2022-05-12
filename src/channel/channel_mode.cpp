#include "channel_mode.hpp"

ChannelMode::ChannelMode() : opper_(0)
{
}

ChannelMode::~ChannelMode()
{
}

void    ChannelMode::setChan(std::string name)
{
    channel_ = name;
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

void    ChannelMode::seton(char c, std::istringstream& ss, Client& cl, std::string& reply)
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
            {
                setBan(word);
                opper_ |= (1 << 5);
            }
            else
                getBan(cl.getNick(), reply);
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

void    ChannelMode::setMode(std::string str, std::string arg, Client& cl, std::string& reply)
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
                seton(str[i++], ss, cl, reply);
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

void    ChannelMode::setBan(std::string name)
{
    name += "!*@*";
    for (std::set<std::pair<std::string, unsigned int> >::iterator it = banList_.begin(); it != banList_.end(); it++)
    {
        if (it->first == name)
            return;
    }
    banList_.insert(std::make_pair(name, (unsigned)time(NULL)));
}

template<typename T>
static std::string to_string(const T & value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}


std::string ChannelMode::getBan(std::string nick, std::string& reply)
{
    reply = "";
    for (std::set<std::pair<std::string, unsigned int> >::iterator it = banList_.begin(); it != banList_.end(); it++)
        reply += RPL_BANLIST(nick, channel_, it->first, to_string(it->second));
    reply += RPL_ENDOFBANLIST(nick, channel_);
    return reply;
}