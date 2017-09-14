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
public:
    MessageMutable(int expected_size = 1, std::initializer_list<SourceID> sources = {});
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

    /**
     * @brief Append an entry to the message
     * @param name Name of the entry
     * @param value Value of the entry
     */
    void append(std::string name, int value);

    /**
     * @brief Append an entry to the message
     * @param name Name of the entry
     * @param value Value of the entry
     */
    void append(std::string name, double value);

    /**
     * @brief Append an entry to the message
     * @param name Name of the entry
     * @param value Value of the entry
     */
    void append(std::string name, std::string value);

    /**
     * @brief Append an entry to the message
     * @param name Name of the entry
     * @param value Value of the entry
     */
    void append(std::string name, Message &&value);

    /**
     * @brief Append an entry to the message
     * @param entry The entry to append
     */
    void append(const Message::Entry &entry);

    /**
     * @brief Get a mutable iterator pointing to the first entry
     * @return Mutable iterator pointing to the first entry
     *
     * Makes this class usable in range-based for loops.
     */
    std::vector<Message::Entry>::const_iterator begin(void);

    /**
     * @brief Get a mutable iterator pointing after the last entry
     * @return Mutable iterator pointing after the last entry
     *
     * Makes this class usable in range-based for loops.
     */
    std::vector<Message::Entry>::const_iterator end(void);

    /**
     * @brief Get const iterator pointing to the first entry
     * @return Const iterator pointing to the first entry
     */
    std::vector<Message::Entry>::const_iterator cbegin(void) const;

    /**
     * @brief Get const iterator pointing after the last entry
     * @return Const iterator pointing after the last entry
     */
    std::vector<Message::Entry>::const_iterator cend(void) const;
};

#endif // MESSAGE_M_H
