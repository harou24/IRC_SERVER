#include "commands.hpp"

template<typename T>
static std::string to_string(const T & value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

std::string		topic_reply(const CmdController& controller)
{
	Channel *channel = &controller.getServer().getChannel(controller.getParser().getArgument().arg1);
    Client *cl = controller.getServer().getClientByStream(controller.getCurrentMsg().getStreamPtr());

	if (channel->getMode().getTopic().topic.empty())
		return std::string(RPL_NOTOPIC(cl->getNick(), channel->getChannelName()));

	std::string topic_reply = std::string(RPL_TOPIC(cl->getNick(), channel->getChannelName(), channel->getMode().getTopic().topic));
	topic_reply += std::string(RPL_TOPICWHOTIME(cl->getNick(), channel->getChannelName(), channel->getMode().getTopic()));
	return topic_reply;
}

std::string		set_topic(const CmdController& controller)
{
    Channel *channel = &controller.getServer().getChannel(controller.getParser().getArgument().arg1);
    Client *cl = controller.getServer().getClientByStream(controller.getCurrentMsg().getStreamPtr());

	channel->getMode().setTopic(controller.getParser().getArgument().arg2, cl->getNick(), to_string((unsigned)time(NULL)), *cl);
	channel->sendMessage(*cl, std::string(RPL_TOPICSET(cl, channel->getChannelName(), controller.getParser().getArgument().arg2)));
	return std::string(RPL_TOPICSET(cl, channel->getChannelName(), controller.getParser().getArgument().arg2));
}

std::string		topic(const CmdController& controller)
{
    std::string channel_name = controller.getParser().getArgument().arg1;
    Client *cl = controller.getServer().getClientByStream(controller.getCurrentMsg().getStreamPtr());
    if (controller.getParser().getArgument().arg1.empty())
        return std::string(ERR_NEEDMOREPARAMS(cl->getNick(), "TOPIC")) + std::string(ERR_HELPTOPIC(cl->getNick(), "TOPIC"));
    if (!controller.getServer().isChannel(channel_name))
        return std::string(ERR_NOSUCHCHANNEL(cl->getNick(), channel_name));
    Channel *channel = &controller.getServer().getChannel(channel_name);
    if (controller.getParser().getArgument().arg2.empty())
        return topic_reply(controller);
    if (!channel->isInChannel(cl->getNick()))
        return std::string(ERR_NOTONCHANNEL(cl->getNick(), channel_name));
    if (!(channel->getMode().getModus() & (1<<2)) || channel->isOperator(*cl))
        return set_topic(controller);
    return std::string(ERR_CHANOPRIVSNEEDED(cl->getNick(), channel_name));
}
