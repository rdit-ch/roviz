
#include "streams/image_m.h"
#include "streams/image_p.h"

ImageMutable::ImageMutable()
    : Image()
{
}

#ifdef QT_PRESENT
ImageMutable::ImageMutable(QImage img, std::initializer_list<SourceID> sources)
    : Image(img, sources)
{
}
#endif

#ifdef OPENCV_PRESENT
ImageMutable::ImageMutable(cv::Mat img, std::initializer_list<SourceID> sources)
    : Image(img, sources)
{
}
#endif

ImageMutable::ImageMutable(int w, int h, Image::Format f, std::initializer_list<SourceID> sources)
    : Image(false, sources)
{
    _this->is_self_managed = true;
    _this->init(w, h, f); // Needs to be before the malloc!
    _this->data_ptr = static_cast<unsigned char*>(std::malloc(this->dataLength()));

#ifdef QT_PRESENT
    _this->qt_img = QImage(_this->data_ptr, this->width(), this->height(), QImage::Format_Grayscale8);
#endif

#ifdef OPENCV_PRESENT
    // OpenCV isn't color friendly, they use BGR and don't support RGB555!
    // Only grayscale is supported for now...
    _this->cv_img = cv::Mat(this->height(), this->width(), CV_8UC1, _this->data_ptr);
#endif
}

unsigned char *ImageMutable::data()
{
    return _this->data_ptr;
}
