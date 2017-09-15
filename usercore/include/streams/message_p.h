#ifndef MESSAGEPRIVATE_H
#define MESSAGEPRIVATE_H

#include <functional>
#include "streams/stream_object_p.h"
#include "message.h"

/**
 * @brief Private part of the Message class
 *
 * \sa Message
 */
class MessagePrivate : public StreamObjectPrivate
{
public:
    std::vector<Message::Entry> entries;
    Message::Entry default_entry;
    std::string type;

    class EntryPrivate;
};

class MessageEntryPrivate
{
public:
    MessageEntryPrivate();
    MessageEntryPrivate(void *value, std::function<void (void*)> deleter);
    std::unique_ptr<void, std::function<void (void*)> > value;
    std::string name;
    size_t type;
};

#endif // MESSAGEPRIVATE_H
