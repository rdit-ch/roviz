
#include "portable/portable_image_mutable.h"
#include "portable/portable_image_p.h"

PortableImageMutable::PortableImageMutable()
    : PortableImage()
{
}

#ifdef QT_PRESENT
PortableImageMutable::PortableImageMutable(QImage img, std::initializer_list<SourceID> sources)
    : PortableImage(img, sources)
{
}
#endif

#ifdef OPENCV_PRESENT
PortableImageMutable::PortableImageMutable(cv::Mat img, std::initializer_list<SourceID> sources)
    : PortableImage(img, sources)
{
}
#endif

PortableImageMutable::PortableImageMutable(int w, int h, PortableImage::Format f, std::initializer_list<SourceID> sources)
{
    _this->is_self_managed = true;
    _this->init(w, h, f, sources);
    _this->mem.reset(static_cast<unsigned char*>(operator new(this->dataLength())), &PortableImagePrivate::deleter);
    _this->data_ptr = _this->mem.get();
#ifdef QT_PRESENT
    _this->qt_img = QImage(_this->data_ptr, this->width(), this->height(), QImage::Format_Grayscale8);
#endif
#ifdef OPENCV_PRESENT
    // OpenCV isn't color friendly, they use BGR and don't support RGB555!
    // Only grayscale is supported for now...
    _this->cv_img = cv::Mat(this->height(), this->width(), CV_8UC1, _this->data_ptr);
#endif
}

PortableImageMutable::~PortableImageMutable()
{
}

unsigned char *PortableImageMutable::data()
{
    return _this->data_ptr;
}
