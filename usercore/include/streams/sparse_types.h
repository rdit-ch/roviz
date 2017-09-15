#ifndef SPARSE_TYPES_H
#define SPARSE_TYPES_H

#include "core/export_handling.h"

#define DO_FOR_ALL_SPARSE_TYPES(EXPR) \
    EXPR(Point2D) \
    EXPR(Point2F) \
    EXPR(Point3D) \
    EXPR(Point3F) \
    EXPR(Rect) \
    EXPR(RectF) \
    EXPR(Circle) \
    EXPR(CircleF)

// Didn't find a way yet without duplicating it
#define DO_FOR_ALL_SPARSE(EXPR) \
    EXPR(Sparse<Point2D>) \
    EXPR(Sparse<Point2F>) \
    EXPR(Sparse<Point3D>) \
    EXPR(Sparse<Point3F>) \
    EXPR(Sparse<Rect>) \
    EXPR(Sparse<RectF>) \
    EXPR(Sparse<Circle>) \
    EXPR(Sparse<CircleF>)

class ROVIZ_EXPORT Point2D
{
    public:
        int x, y, group;

        Point2D() = default;
        Point2D(int _x, int _y, int _g = 0);
};

class ROVIZ_EXPORT Point2F
{
public:
    double x, y; int group;

    Point2F() = default;
    Point2F(double _x, double _y, int _g = 0);

};

class ROVIZ_EXPORT Point3D
{
public:
    int x, y, z, group;

    Point3D() = default;
    Point3D(int _x, int _y, int _z, int _g = 0);
};

class ROVIZ_EXPORT Point3F
{
public:
    double x, y, z; int group;

    Point3F() = default;
    Point3F(double _x, double _y, double _z, int _g = 0);
};

class ROVIZ_EXPORT Rect
{
public:
    int left, top, width, height, group;

    Rect() = default;
    Rect(int _l, int _t, int _h, int _w, int _g = 0);
};

class ROVIZ_EXPORT RectF
{
public:
    double left, top, width, height; int group;

    RectF() = default;
    RectF(double _l, double _t, double _h, double _w, double _g = 0);
};

class ROVIZ_EXPORT Circle
{
public:
    int x, y, r, group;

    Circle() = default;
    Circle(int _x, int _y, int _r, int _g = 0);
};

class ROVIZ_EXPORT CircleF
{
public:
    double x, y, r; int group;

    CircleF() = default;
    CircleF(double _x, double _y, double _r, double _g = 0);
};

#endif // SPARSE_TYPES_H
