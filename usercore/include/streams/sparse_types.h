#ifndef SPARSE_TYPES_H
#define SPARSE_TYPES_H

#include "core/export_handling.h"

#define ROVIZ_DO_FOR_ALL_SPARSE_TYPES(EXPR) \
    EXPR(roviz::Point2D) \
    EXPR(roviz::Point3D) \
    EXPR(roviz::Rect) \
    EXPR(roviz::Circle)

// Didn't find a way yet without duplicating it
#define ROVIZ_DO_FOR_ALL_SPARSE(EXPR) \
    EXPR(roviz::Sparse<roviz::Point2D>) \
    EXPR(roviz::Sparse<roviz::Point3D>) \
    EXPR(roviz::Sparse<roviz::Rect>) \
    EXPR(roviz::Sparse<roviz::Circle>)

namespace roviz
{

class ROVIZ_EXPORT Point2D
{
public:
    double x, y; int group;

    Point2D() = default;
    ~Point2D() = default;
    Point2D(double _x, double _y, int _g = 0);

};

class ROVIZ_EXPORT Point3D
{
public:
    double x, y, z; int group;

    Point3D() = default;
    ~Point3D() = default;
    Point3D(double _x, double _y, double _z, int _g = 0);
};

class ROVIZ_EXPORT Rect
{
public:
    double left, top, width, height; int group;

    Rect() = default;
    ~Rect() = default;
    Rect(double _l, double _t, double _h, double _w, double _g = 0);
};

class ROVIZ_EXPORT Circle
{
public:
    double x, y, r; int group;

    Circle() = default;
    ~Circle() = default;
    Circle(double _x, double _y, double _r, double _g = 0);
};

}

#endif // SPARSE_TYPES_H
