#ifndef TEMPLATEDECL_H
#define TEMPLATEDECL_H

#include "core/export_handling.h"
#include "core/template_decl_helpers.h"

// Including the header here leads to a circular inclusion
class Image;
class Message;
template<class T> class Sparse;
class Point2D;
class Point2F;
class Point3D;
class Point3F;
class Rect;
class RectF;
class Circle;
class CircleF;

// Make sure all templates for the streams get instantiated
#define DO_FOR_ALL_STREAMS(EXPR) \
    EXPR(Image) \
    EXPR(Message) \
    DO_FOR_ALL_SPARSE_TEMPLATES(EXPR)

#define DO_FOR_ALL_SPARSE(EXPR) \
    EXPR(Point2D) \
    EXPR(Point2F) \
    EXPR(Point3D) \
    EXPR(Point3F) \
    EXPR(Rect) \
    EXPR(RectF) \
    EXPR(Circle) \
    EXPR(CircleF)

// Didn't find a way yet without duplicating it
#define DO_FOR_ALL_SPARSE_TEMPLATES(EXPR) \
    EXPR(Sparse<Point2D>) \
    EXPR(Sparse<Point2F>) \
    EXPR(Sparse<Point3D>) \
    EXPR(Sparse<Point3F>) \
    EXPR(Sparse<Rect>) \
    EXPR(Sparse<RectF>) \
    EXPR(Sparse<Circle>) \
    EXPR(Sparse<CircleF>)

#endif // TEMPLATEDECL_H
