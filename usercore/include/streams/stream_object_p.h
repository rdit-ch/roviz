#ifndef STREAM_OBJECT_P_H
#define STREAM_OBJECT_P_H

#include "stream_object.h"

/**
 * @brief Private part of the StreamObject class
 *
 * \sa StreamObject
 */
class StreamObjectPrivate
{
public:
    SourceID id;

    StreamObjectPrivate() = default;
    virtual ~StreamObjectPrivate() = default;
};

#endif // STREAM_OBJECT_P_H
