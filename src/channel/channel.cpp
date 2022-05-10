#include "channel.hpp"

Channel::Channel() :opper_(0){}

Channel::Channel(std::string name, Client& cl) : name_(name), opper_(0)
{
    clients_.insert(&cl);
    operators_.insert(&cl);
}

Channel::~Channel()
{
    clients_.clear();
    operators_.clear();
}

std::set<Client *>::iterator    Channel::getClientByName(std::set<Client *>& set, std::string name) const
{
    for (std::set<Client *>::iterator it = set.begin(); it != set.end(); it++)
    {
        if (std::strcmp((*it)->getNick().c_str(), name.c_str()) == 0)
            return it;
    }
    return set.end();
}

void        Channel::addClient(Client& cl)
{
    std::cout << "adding " << cl.getNick() << " to channel\n";
    clients_.insert(&cl);
}

void        Channel::removeClient(Client& cl, std::string reply)
{
    std::set<Client *>::iterator it = getClientByName(clients_, cl.getNick());
    std::set<Client *>::iterator it_op = getClientByName(operators_, cl.getNick());
    if (it != clients_.end())
    {
        if (isActive())
            sendMessage(cl, reply);
        clients_.erase(*it);
    }
    if (it_op != operators_.end())
        operators_.erase(*it_op);
}

void        Channel::addOperator(Client& cl)
{
    operators_.insert(&cl);
}

void        Channel::removeOperator(Client& cl)
{
    std::set<Client *>::iterator it = getClientByName(operators_, cl.getNick());
    if (it != operators_.end())
        operators_.erase(it);
}

bool        Channel::isInChannel(std::string nick)
{
    for (std::set<Client *>::iterator it = clients_.begin(); it != clients_.end(); it++)
    {
        if ((*it)->getNick() == nick)
            return true;
    }
    return false;
}

bool        Channel::isOperator(Client& cl)
{
    std::set<Client *>::iterator it = getClientByName(operators_, cl.getNick());
    if (it != operators_.end())
        return true;
    return false;
}

bool        Channel::isActive() const
{
    if (clients_.size() > 0)
        return true;
    return false;
}

std::string Channel::getNames()
{
    std::string names = "";

    for(std::set<Client *>::const_iterator it = clients_.begin(); it != clients_.end(); it++)
    {
        if (names.length() > 0 && !isOperator(*(*it)))
            names += " " + (*it)->getNick();
        else if (names.length() > 0 && isOperator(*(*it)))
            names += " @" + (*it)->getNick();
        else if (isOperator(*(*it)))
            names = "@" + (*it)->getNick();
        else
            names = (*it)->getNick();
    }
    return names;
}

std::string Channel::getChannelName() const
{
    return name_;
}


void        Channel::sendMessage(Client& cl, std::string msg)
{
    for(std::set<Client *>::const_iterator it = clients_.begin(); it != clients_.end(); it++)
    {
        if ((*it)->getNick() != cl.getNick())
            (*it)->getStream().send(msg, msg.length());
    }
}

bool    Channel::Invite() const
{
    std::cout << opper_ << std::endl;
    return (opper_ & (1<<1));
}

bool    Channel::isInvite(const Client& cl)
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

void    Channel::addInvite(Client& cl)
{
    inventation_.insert(&cl);
}

void    Channel::seton(char c)
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

void    Channel::setoff(char c)
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

void    Channel::setMode(std::string str)
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
