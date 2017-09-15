#ifndef MESSAGEPRIVATE_H
#define MESSAGEPRIVATE_H

#include "message.h"
#include "streams/stream_object_p.h"

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

    ~MessagePrivate() = default;
};

#endif // MESSAGEPRIVATE_H
