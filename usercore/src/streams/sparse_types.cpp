
#include "streams/sparse_types.h"

Point2D::Point2D(int _x, int _y, int _g)
    : x(_x), y(_y), group(_g)
{
}

Point2F::Point2F(double _x, double _y, int _g)
    : x(_x), y(_y), group(_g)
{
}

Point3D::Point3D(int _x, int _y, int _z, int _g)
    : x(_x), y(_y), z(_z), group(_g)
{
}

Point3F::Point3F(double _x, double _y, double _z, int _g)
    : x(_x), y(_y), z(_z), group(_g)
{
}

Rect::Rect(int _l, int _t, int _h, int _w, int _g)
    : left(_l), top(_t), width(_w), height(_h), group(_g)
{
}

RectF::RectF(double _l, double _t, double _h, double _w, double _g)
    : left(_l), top(_t), width(_w), height(_h), group(_g)
{
}

Circle::Circle(int _x, int _y, int _r, int _g)
    : x(_x), y(_y), r(_r), group(_g)
{
}

CircleF::CircleF(double _x, double _y, double _r, double _g)
    : x(_x), y(_y), r(_r), group(_g)
{
}
