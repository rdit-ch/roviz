
#include "core/point_stream.h"

void PointStream::init()
{
    AbstractItem::registerConnectorStyle(Qt::yellow, qMetaTypeId<PointStream*>());
}

PointStream::PointStream(QObject *parent)
    : QObject(parent)
{
}

PointStream::~PointStream()
{
}
