#include "message.hpp"

Message::Message() {}

Message::Message(const std::string& data, TcpStream *stream): data_(data), stream_(stream) { }

Message::~Message() { }

std::string Message::getData() const { return data_; }

TcpStream&  Message::getStream() const { return *stream_; }

TcpStream*  Message::getStreamPtr() { return stream_; }

