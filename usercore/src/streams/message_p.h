#ifndef MESSAGEPRIVATE_H
#define MESSAGEPRIVATE_H

#include <functional>
#include "streams/stream_object_p.h"
#include "streams/message.h"

namespace roviz
{

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
};

}

#endif // MESSAGEPRIVATE_H
