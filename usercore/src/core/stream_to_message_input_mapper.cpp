
#include "core/stream_to_message_input_mapper.h"

StreamToMessageInputMapper::StreamToMessageInputMapper(QObject *parent)
    : QObject(parent)
{

}

StreamToMessageInputMapper::~StreamToMessageInputMapper()
{

}

void StreamToMessageInputMapper::inputMapper(Message message)
{
    emit this->newMessage(this->input, message);
}
