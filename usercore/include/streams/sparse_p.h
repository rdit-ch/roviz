#ifndef SPARSE_P_H
#define SPARSE_P_H

#include "core/export_handling.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include <QPainter>
#include <QLabel>
#endif

#include <vector>
#include "streams/stream_object_p.h"
#include "streams/image.h"
#include "streams/sparse.h"

template<class T>
class SparsePrivate : public StreamObjectPrivate
{
public:
    std::vector<T> data;
    T default_value;
    Image base_image;
};

#endif // SPARSE_P_H
