#ifndef MESSAGEPRIVATE_H
#define MESSAGEPRIVATE_H

#include "message.h"

class MessagePrivate
{
public:
    Message *_this;
    SourceID id;
    std::vector<Message::Entry> entries;

    MessagePrivate(Message *other);
    ~MessagePrivate();
};

#endif // MESSAGEPRIVATE_H
