
#include "streams/message_m.h"
#include "streams/message_p.h"

MessageMutable::MessageMutable(int expected_size, std::initializer_list<SourceID> sources)
    : Message(sources)
{
    _this->entries.reserve(expected_size);
}

void MessageMutable::append(const std::string &name, const std::string &value)
{
    _this->entries.push_back(Message::Entry(name, value));
}

void MessageMutable::append(Message::Entry &&entry)
{
    _this->entries.push_back(std::move(entry));
}
