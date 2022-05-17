#ifndef CHANNEL_TOPIC_HPP
# define CHANNEL_TOPIC_HPP

# include <string>
# include "client.hpp"

class Client;

class Topic
{
    public:
        Topic();
        ~Topic();

        std::string         creationTimeTopic;
        std::string         topic;
        std::string         topic_nick;
        Client*             writer;
};

#endif