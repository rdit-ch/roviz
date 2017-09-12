
#include "backend_dev/stream_to_input_mapper.h"

#include "item/item_input.h"

StreamToInputMapper::StreamToInputMapper(QObject *parent)
    : QObject(parent)
{
}

void StreamToInputMapper::inputMapper(StreamObject obj)
{
    emit this->newObject(obj, Input(this->input));
}
