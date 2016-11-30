
#include "core/stream_to_image_input_mapper.h"

StreamToImageInputMapper::StreamToImageInputMapper(QObject *parent)
    : QObject(parent)
{
}

StreamToImageInputMapper::~StreamToImageInputMapper()
{
}

void StreamToImageInputMapper::inputMapper(const PortableImage img)
{
    emit this->newImage(img, this->input);
}
