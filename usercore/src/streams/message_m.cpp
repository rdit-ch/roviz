
#include "streams/message_m.h"
#include "streams/message_p.h"

MessageMutable::MessageMutable(std::initializer_list<SourceID> sources)
    : Message(sources)
{
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
