#ifndef POINTSTREAM_H
#define POINTSTREAM_H

#include <QObject>
#include "helper/startup_helper.h"
#include "item/abstract_item.h"
#include "pointcloud.h"

class PointStream : public QObject
{
    Q_OBJECT

public:
    static void init(void);

    explicit PointStream(QObject *parent = 0);
    ~PointStream();

signals:
    void newPoints(Pointcloud points);
};

#endif // POINTSTREAM_H
