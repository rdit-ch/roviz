#ifndef MESSAGE_M_H
#define MESSAGE_M_H

#include "streams/message.h"

/**
 * @brief The mutable version of Message
 *
 * You can manipulate the message data in this class, but it will be always
 * converted to the non-mutable version before it is sent to an item.
 *
 * \sa Message
 */
class MessageMutable : public Message
{
public:
    MessageMutable(std::initializer_list<SourceID> sources = {});
    ~MessageMutable() = default;

    /**
     * @brief Get an entry of the message
     * @param name The name of the entry
     * @return The first entry with a matching name
     *
     * If name is not found in the message, an invalid entry is returned.
     */
    Message::Entry &entry(unsigned int index);

    /**
     * @brief Get an entry of the message
     * @param index The index of the entry
     * @return The entry
     *
     * This function checks the bounds and returns an invalid entry if the index
     * is out of bounds.
     */
    Message::Entry &at(int index);

    /**
     * @brief Get an entry of the message
     * @param index The index of the entry
     * @return The entry
     *
     * WARNING: This function doesn't check the bounds!
     */
    Message::Entry &operator[](int index);
};

#endif // MESSAGE_M_H
