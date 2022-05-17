#include "channel_mode.hpp"

template<typename T>
static std::string to_string(const T & value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

ChannelMode::ChannelMode() : opper_(0)
{
    topic_ = new Topic();
}

ChannelMode::~ChannelMode()
{
    delete topic_;
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
            break;
        case 'b':
            if (ss>>word && word.size() > 0)
            {
                setBan(word, cl.getNick());
                // opper_ |= (1 << 5);
            }
            else
                getBan(cl.getNick(), reply);
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
                offBan(word);
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

void    ChannelMode::setBan(std::string name, std::string nick)
{
    name += "!*@*";
    for (ban_type::iterator it = banList_.begin(); it != banList_.end(); it++)
    {
        if (it->first == name)
            return;
    }
    banList_.push_back(std::make_pair(name, std::make_pair((unsigned)time(NULL), nick)));
}

void    ChannelMode::offBan(std::string name)
{
    for (ban_type::iterator it = banList_.begin(); it != banList_.end(); it++)
    {
        if (it->first == name)
        {
            banList_.erase(it);
            return;
        }
    }
}




std::string ChannelMode::getBan(std::string nick, std::string& reply)
{
    reply = "";
    for (ban_type::iterator it = banList_.begin(); it != banList_.end(); it++)
        reply += RPL_BANLIST(nick, it->second.second, channel_, it->first, to_string(it->second.first));
    reply += RPL_ENDOFBANLIST(nick, channel_);
    return reply;
}

bool        ChannelMode::isBan(std::string name)
{
    name += "!*@*";
    for (ban_type::iterator it = banList_.begin(); it != banList_.end(); it++)
    {
        if (it->first == name)
            return true;
    }
    return false;
}

std::string     ChannelMode::isModeOn()
{
    std::string reply = "";

    if (opper_ & (1<<0))
        reply += "o";
    if (opper_ & (1<<1))
        reply += "i";
    if (opper_ & (1<<2))
        reply += "t";
    if (opper_ & (1<<3))
        reply += "n";
    if (opper_ & (1<<4))
        reply += "l";
    if (opper_ & (1<<5))
        reply += "b";
    if (opper_ & (1<<6))
        reply += "k";
    return reply;
}

void        ChannelMode::setTopic(std::string msg, std::string nick, std::string time, Client& writer)
{
    topic_->creationTimeTopic = time;
    topic_->topic = msg;
    topic_->topic_nick = nick;
    topic_->writer = &writer;
}

const Topic&      ChannelMode::getTopic() const
{
    return *topic_;
}