#include "channel.hpp"

Channel::Channel() {}

Channel::Channel(std::string name, Client& cl) : name_(name)
{
    clients_.insert(&cl);
    operators_.insert(&cl);
}

Channel::~Channel()
{
    clients_.clear();
    operators_.clear();
}

std::set<Client *>::iterator    Channel::getClientByName(std::set<Client *>& set, std::string name)
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

void        Channel::removeClient(Client& cl)
{
    std::set<Client *>::iterator it = getClientByName(clients_, cl.getNick());
    std::set<Client *>::iterator it_op = getClientByName(operators_, cl.getNick());
    if (it != clients_.end())
        clients_.erase(it);
    if (it_op != operators_.end())
        operators_.erase(it_op);
}

void        Channel::addOperator(Client& cl)
{
    operators_.insert(&cl);
}

void        Channel::removeOperator(Client& cl)
{
    std::set<Client *>::iterator it = operators_.find(&cl);
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

bool        Channel::isOperator(Client& cl) const
{
    std::set<Client *>::iterator it = operators_.find(&cl);
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

void        Channel::sendMessage(Client& cl, std::string msg)
{
    std::cout << "SENDING PRIV CHAN MSG\n";
    for(std::set<Client *>::const_iterator it = clients_.begin(); it != clients_.end(); it++)
        std::cout << "name = " << (*it)->getNick() << std::endl;
    for(std::set<Client *>::const_iterator it = clients_.begin(); it != clients_.end(); it++)
    {
        std::cout << (*it)->getNick() << " SENDING PRIV CHAN MSG\n";
        if ((*it)->getNick() != cl.getNick())
            (*it)->getStream().send(msg, msg.length());
    }
}