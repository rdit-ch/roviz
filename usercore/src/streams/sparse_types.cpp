
#include "streams/sparse_types.h"

namespace roviz
{

Point2D::Point2D(double _x, double _y, int _g)
    : x(_x), y(_y), group(_g)
{
}

Point3D::Point3D(double _x, double _y, double _z, int _g)
    : x(_x), y(_y), z(_z), group(_g)
{
}

Rect::Rect(double _l, double _t, double _h, double _w, double _g)
    : left(_l), top(_t), width(_w), height(_h), group(_g)
{
}

Circle::Circle(double _x, double _y, double _r, double _g)
    : x(_x), y(_y), r(_r), group(_g)
{
}

}
