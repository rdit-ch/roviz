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
class ROVIZ_EXPORT MessageMutable : public Message
{
COPY_DELETE(MessageMutable)
MOVE_DEFAULT(MessageMutable)

public:
    MessageMutable(std::string msg_type = "Generic", std::initializer_list<SourceID> sources = {}, int expected_size = 1);
    ~MessageMutable() = default;

    /**
     * @brief Append an entry to the message
     * @param name Name of the entry
     * @param value Value of the entry
     *
     * Note: T has to be copy-constructable.
     */
    void append(const std::string &name, int value);

    /**
     * @brief Append an entry to the message
     * @param name Name of the entry
     * @param value Value of the entry
     */
    void append(const std::string &name, double value);

    /**
     * @brief Append an entry to the message
     * @param name Name of the entry
     * @param value Value of the entry
     */
    void append(const std::string &name, const std::string &value);

    /**
     * @brief Append an entry to the message
     * @param name Name of the entry
     * @param value Value of the entry
     */
    void append(const std::string &name, bool value);

    /**
     * @brief Append an entry to the message
     * @param entry The entry to append
     *
     * This function takes ownership of the entry, which means that it
     * needs to be moved with std::move.
     */
    void append(Entry &&entry);
};

#endif // MESSAGE_M_H
