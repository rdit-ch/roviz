
#include "core/message_stream.h"

STARTUP_ADD_COMPONENT(MessageStream)

void MessageStream::init()
{
    AbstractItem::registerConnectorStyle(Qt::red, qMetaTypeId<MessageStream*>());
}

MessageStream::MessageStream(QObject *parent)
    : QObject(parent)
{
}

MessageStream::~MessageStream()
{
}
