#ifndef MESSAGE_H
#define MESSAGE_H

#include <typeinfo>
#include <functional>
#include <string>
#include <initializer_list>
#include "core/export_handling.h"
#include "streams/stream_object.h"

class OutputPrivate;
class StreamWidget;
class MessageWidget;
class MessagePrivate;

/**
 * @brief Used to send messages across streams
 *
 * This class provides an interface to send generic messages across streams.
 * This could be useful for control signals or the like. It consists of a list
 * of entries. Each entry has a name and a value. The type of the value can be
 * either int, double or string.
 *
 * \sa MessageMutable
 * \sa MessagePrivate
 */
class ROVIZ_EXPORT Message : public StreamObject
{
friend class MessageWidget;

COPY_DEFAULT(Message)
MOVE_DEFAULT(Message)

public:
    class Entry;

    Message(const StreamObject &base);
    Message(std::string msg_type = "Generic", std::initializer_list<SourceID> sources = {});
    virtual ~Message() = default;

    /**
     * @brief Get an entry of the message
     * @param name The name of the entry
     * @return The first entry with a matching name
     *
     * If name is not found in the message, an invalid entry is returned.
     */
    const Entry &entry(const std::string &name) const;

    /**
     * @brief Get an entry of the message
     * @param index The index of the entry
     * @return The entry
     *
     * This function checks the bounds and returns an invalid entry if the index
     * is out of bounds.
     */
    const Entry &at(int index) const;

    /**
     * @brief Get an entry of the message
     * @param index The index of the entry
     * @return The entry
     *
     * WARNING: This function doesn't check the bounds!
     */
    const Entry &operator[](int index) const;

    /**
     * @brief Get the size of a message
     * @return The amount of entries of this message
     */
    int size(void) const;

    /**
     * @brief Get the type of the message
     * @return Type of the message
     *
     * With the type of a message, the receiver can check if it understands this
     * message format.
     */
    std::string type(void) const;

    /**
     * @brief Get const iterator pointing to the first entry
     * @return Const iterator pointing to the first entry
     *
     * Makes this class usable in range-based for loops.
     */
    std::vector<Message::Entry>::const_iterator begin(void) const;

    /**
     * @brief Get const iterator pointing after the last entry
     * @return Const iterator pointing after the last entry
     *
     * Makes this class usable in range-based for loops.
     */
    std::vector<Message::Entry>::const_iterator end(void) const;

protected:
    MessagePrivate *_this;

// Handle the displaying of the message
#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
public:
    static StreamWidget *initWidget(OutputPrivate *out);
#endif
};

/**
 * @brief An entry of a message
 *
 * Be sure you call the correct access function by always checking 'type' first!
 */
class Message::Entry
{
COPY_DELETE(Entry)
MOVE_DEFAULT(Entry)

public:
    Entry() = default;
    Entry(const std::string &name, const std::string &value);

    std::string name(void) const;
    std::string value(void) const;

    template<typename T>
    T to(void) const;

private:
    std::string name_var;
    std::string value_var;
};

DECLARE_STREAM_OBJECT(Message)

#endif // MESSAGE_H
