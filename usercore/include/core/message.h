#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <initializer_list>
#include <memory>
#include "portable/portable_image.h"

class MessagePrivate;

// Right now, the Message class doesn't implement implicit data sharing. It
// may at some point in the future though, if we need to share bigger messages.
class Message
{
public:
    struct Entry
    {
        std::string name;

        enum Type
        {
            Invalid,
            String,
            Int,
            Double
        } type;

        std::string s;
        int i;
        double d;
    };

    Message(std::initializer_list<SourceID> sources = {});

    // The std::unique_ptr cannot be automatically copied
    Message(const Message &other);
    Message &operator=(const Message &other);
    virtual ~Message();

    Entry entry(unsigned int index);
    Entry at(int index);
    Entry operator[](int index);
    SourceID id(void);

private:
    std::unique_ptr<MessagePrivate> _this;
};

#endif // MESSAGE_H
