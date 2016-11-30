#ifndef PORTABLEIMAGEPRIVATE_H
#define PORTABLEIMAGEPRIVATE_H

#include <vector>
#include <memory>
#include <initializer_list>
#include "portable/portable_image.h"

class PortableImagePrivate
{
public:
    PortableImage *_this;
#ifdef QT_PRESENT
    QImage qt_img;
#endif
#ifdef OPENCV_PRESENT
    cv::Mat cv_img;
#endif
    unsigned char *data_ptr;
    bool is_self_managed;
    std::shared_ptr<unsigned char> mem;
    int w, h, bits, bytes, len;
    enum PortableImage::Format f;
    SourceID id;

    PortableImagePrivate(PortableImage *q);
    void init(int w, int h, enum PortableImage::Format f, std::initializer_list<SourceID> sources);
    static void deleter(unsigned char *target);
};

#endif // PORTABLEIMAGEPRIVATE_H
