
#include "core/message.h"
#include "core/message_p.h"

Message::Message(std::initializer_list<SourceID> sources)
    : _this(new MessagePrivate(this))
{
    if(sources.size() == 0)
    {
        _this->id = nullptr;
    }
    else
    {
        _this->id = std::make_shared<ImageSrcTreeNode>();
        _this->id->sources = std::vector<SourceID>(sources);
    }
}

Message::Message(const Message &other)
    : _this(new MessagePrivate(this))
{
    *_this = *other._this;
}

Message &Message::operator=(const Message &other)
{
    *_this = *other._this;
    return *this;
}

Message::~Message()
{
}

Message::Entry Message::entry(unsigned int index)
{
    if(index > _this->entries.size())
        return Message::Entry();

    return _this->entries[index];
}

Message::Entry Message::at(int index)
{
    return this->entry(index);
}

Message::Entry Message::operator[](int index)
{
    return _this->entries[index];
}

SourceID Message::id()
{
    return _this->id;
}
