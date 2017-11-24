#ifndef TEMPLATEDECL_H
#define TEMPLATEDECL_H

#include "core/export_handling.h"

// Defines DO_FOR_ALL_SPARSE
#include "streams/sparse_types.h"

// Including the header here leads to a circular inclusion
namespace roviz
{
    class Image;
    class Message;
    template<class T> class Sparse;
}

// Make sure all templates for the streams get instantiated
#define ROVIZ_DO_FOR_ALL_STREAMS(EXPR) \
    EXPR(roviz::Image) \
    EXPR(roviz::Message) \
    ROVIZ_DO_FOR_ALL_SPARSE(EXPR)

#endif // TEMPLATEDECL_H
