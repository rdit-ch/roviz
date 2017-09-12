#ifndef IMAGEQUEUE_H
#define IMAGEQUEUE_H

#include <list>
#include <mutex>
#include "core/export_handling.h"
#include "streams/stream_object.h"

/**
 * @brief A queue to buffer input stream objects
 *
 * Used to queue streams that arrive at item inputs.
 *
 * \sa RovizItem
 * \sa StreamObject
 */
class ROVIZ_EXPORT_CLASS InputQueue
{
public:
    std::mutex mtx;

    InputQueue();

    /**
     * @brief Push an object into the queue
     * @param obj The object to push in the queue
     */
    void push(StreamObject obj);

    /**
     * @brief Get the next object in the queue
     * @return The next object in the queue
     */
    StreamObject next(void);

    /**
     * @brief Get the newest object in the queue
     * @return The newest object in the queue
     *
     * Discards all older objects
     */
    StreamObject newest(void);

    /**
     * @brief Check whether an object is available
     * @return True if an object is available, false otherwise
     */
    bool available(void);

private:
    std::list<StreamObject> objects;
};

#endif // IMAGEQUEUE_H
