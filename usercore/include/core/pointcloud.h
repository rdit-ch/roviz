#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include <vector>
#include <memory>
#include <array>
#include "portable/portable_item_global.h"
#include "portable/portable_image.h"

class PointcloudPrivate;

/**
 * @brief A point is simply an array of doubles. The downside of this is, that
 * it is not very secure because you have to know the dimensions before, but
 * on the other hand it allows a very fast access, because a pointcloud will
 * internally be represented by a contiguous array of doubles, allowing very
 * fast access. This representation was chosen, because operating on large
 * pointclouds might become a quite resource-intensive task and the points
 * have to be as optimized as possible to reduce the overhead.
 */
typedef double* Point;

class PORTABLE_EXPORT_CLASS Pointcloud
{
public:
    Pointcloud(std::initializer_list<SourceID> sources = {});
    virtual ~Pointcloud();

    // The std::unique_ptr cannot be automatically copied
    Pointcloud(const Pointcloud &other);
    Pointcloud &operator =(const Pointcloud &other);

    Pointcloud(const int dim);
    Pointcloud(const int dim, SourceID id);
    Point first(void);
    Point last(void);
    size_t size(void);
    Point operator[](unsigned int i);
    Point at(unsigned int i);
    int dimension(void);
    SourceID id(void);

protected:
    std::unique_ptr<PointcloudPrivate> _this;
};

#endif // POINTCLOUD_H
