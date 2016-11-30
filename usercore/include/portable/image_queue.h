#ifndef IMAGEQUEUE_H
#define IMAGEQUEUE_H

#include <list>
#include <mutex>
#include "portable/portable_item_global.h"
#include "portable/portable_image.h"

class PortableImage;

/**
 * @brief A queue to buffer PortableImage objects
 *
 * Used to queue images that arrive at item inputs.
 *
 * \ingroup robot_framework
 */
class PORTABLE_EXPORT_CLASS ImageQueue
{
public:
    std::mutex mtx;

    ImageQueue();

    /**
     * @brief Push an image into the queue
     * @param img The image to push in the queue
     */
    void push(PortableImage img);

    /**
     * @brief Get the next image in the queue
     * @return The next image in the queue
     */
    PortableImage next(void);

    /**
     * @brief Get the newest image in the queue
     * @return The newest image in the queue
     *
     * Discards all older images
     */
    PortableImage newest(void);

    /**
     * @brief Check whether an image is available
     * @return True if an image is available, false otherwise
     */
    bool available(void);

private:
    std::list<PortableImage> images;
};

#endif // IMAGEQUEUE_H
