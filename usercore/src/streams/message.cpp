
#include "streams/message.h"
#include "streams/message_p.h"

#include <QWidget>

Message::Message(const StreamObject &base)
{
    _this_base = base._this_base;
}

Message::Message(std::initializer_list<SourceID> sources)
    : _this(new MessagePrivate())
{
    _this_base.reset(_this);
    this->initSources(sources);
}

const Message::Entry &Message::entry(const std::string &name) const
{
    for(const auto &e : _this->entries)
        if(e.name == name)
            return e;

    // Return something invalid if nothing's found
    return _this->default_entry;
}

const Message::Entry &Message::at(int index) const
{
    if(index < this->size() - 1)
        return _this->entries[index];

    // Return something invalid if the index is out of bounds
    return _this->default_entry;
}

const Message::Entry &Message::operator[](int index) const
{
    return _this->entries[index];
}

int Message::size() const
{
    return _this->entries.size();
}

#ifndef ROVIZ_EXPORT
QWidget *Message::initWidget(StreamBase *)
{
    // TODO Implement
    return new QWidget();
}
#endif
