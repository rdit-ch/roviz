
#include "core/image_stream.h"

STARTUP_ADD_COMPONENT(ImageStream)
Q_DECLARE_METATYPE(PortableImage)

void ImageStream::init()
{
    AbstractItem::registerConnectorStyle(Qt::green, qMetaTypeId<ImageStream*>());
    qRegisterMetaType<PortableImage>();
}

ImageStream::ImageStream(QObject *parent)
    : QObject(parent)
{
}

ImageStream::~ImageStream()
{
}
