
#include "streams/message_m.h"
#include "streams/message_p.h"

MessageMutable::MessageMutable(int expected_size, std::initializer_list<SourceID> sources)
    : Message(sources)
{
    _this->entries.reserve(expected_size);
}

Message::Entry &MessageMutable::entry(unsigned int index)
{
    if(index > _this->entries.size())
        return _this->default_entry;

    return _this->entries[index];
}

Message::Entry &MessageMutable::at(int index)
{
    return this->entry(index);
}

Message::Entry &MessageMutable::operator[](int index)
{
    return _this->entries[index];
}

void MessageMutable::append(const std::string &name, const std::string &value)
{
    _this->entries.push_back(Message::Entry(name, value));
}

void MessageMutable::append(Message::Entry &&entry)
{
    _this->entries.push_back(std::move(entry));
}

std::vector<Message::Entry>::const_iterator MessageMutable::begin()
{
    return _this->entries.begin();
}

std::vector<Message::Entry>::const_iterator MessageMutable::end()
{
    return _this->entries.end();
}

std::vector<Message::Entry>::const_iterator MessageMutable::cbegin() const
{
    return _this->entries.cbegin();
}

std::vector<Message::Entry>::const_iterator MessageMutable::cend() const
{
    return _this->entries.cend();
}
