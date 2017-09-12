#ifndef PORTABLEIMAGEPRIVATE_H
#define PORTABLEIMAGEPRIVATE_H

#include <memory>
#include <QImage>
#include "streams/image.h"
#include "streams/stream_object_p.h"

/**
 * @brief Private part of the Image class
 *
 * \sa Image
 */
class ImagePrivate : public StreamObjectPrivate
{
public:
#ifdef QT_PRESENT
    QImage qt_img;
#endif
#ifdef OPENCV_PRESENT
    cv::Mat cv_img;
#endif
    unsigned char *data_ptr;
    bool is_self_managed;
    int w, h, bits, bytes, len;
    enum Image::Format f;

    ~ImagePrivate();

    /**
     * @brief Initialize some generic properties
     * @param w Width
     * @param h Height
     * @param f Format
     */
    void init(int w, int h, enum Image::Format f);
};

#endif // PORTABLEIMAGEPRIVATE_H
