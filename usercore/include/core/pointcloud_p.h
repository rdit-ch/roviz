#ifndef POINTCLOUDPRIVATE_H
#define POINTCLOUDPRIVATE_H

#include "core/pointcloud.h"

class PointcloudPrivate
{
public:
    Pointcloud *_this;
    int dim;
    SourceID id;
    std::vector<double> raw_points;

    PointcloudPrivate(Pointcloud *p, const int dim);
};

#endif // POINTCLOUDPRIVATE_H
