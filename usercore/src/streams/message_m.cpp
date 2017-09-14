
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

void MessageMutable::append(std::string name, int value)
{
    Message::Entry entry;

    entry.name = name;
    entry.i = value;

    _this->entries.push_back(entry);
}

void MessageMutable::append(std::string name, double value)
{
    Message::Entry entry;

    entry.name = name;
    entry.d = value;

    _this->entries.push_back(entry);
}

void MessageMutable::append(std::string name, std::string value)
{
    Message::Entry entry;

    entry.name = name;
    entry.s = value;

    _this->entries.push_back(entry);
}

void MessageMutable::append(std::string name, Message &&value)
{
    Message::Entry entry;

    entry.name = name;
    entry.m = std::move(value);

    _this->entries.push_back(entry);
}

void MessageMutable::append(const Message::Entry &entry)
{
    _this->entries.push_back(entry);
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
