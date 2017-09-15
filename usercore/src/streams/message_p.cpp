
#include "streams/message_p.h"

MessageEntryPrivate::MessageEntryPrivate()
{
}

MessageEntryPrivate::MessageEntryPrivate(void *value, std::function<void (void *)> deleter)
    : value(value, deleter)
{
}
