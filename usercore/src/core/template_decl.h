#ifndef TEMPLATEDECL_H
#define TEMPLATEDECL_H

#include "core/export_handling.h"

// Defines DO_FOR_ALL_SPARSE
#include "streams/sparse_types.h"

// Including the header here leads to a circular inclusion
class Image;
class Message;
template<class T> class Sparse;

// Make sure all templates for the streams get instantiated
#define DO_FOR_ALL_STREAMS(EXPR) \
    EXPR(Image) \
    EXPR(Message) \
    DO_FOR_ALL_SPARSE(EXPR)

#endif // TEMPLATEDECL_H
