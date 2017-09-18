
#include "streams/image.h"
#include "streams/image_p.h"

#include <memory>
#include "core/template_decl.h"

Image::Image(const StreamObject &base)
{
    this->_this_base = base._this_base;
    _this = dynamic_cast<ImagePrivate*>(this->_this_base.get());
}

Image::Image(std::initializer_list<SourceID> sources)
    : _this(new ImagePrivate())
{
    _this_base.reset(_this);
    this->initSources(sources);

    _this->is_self_managed = false;
    _this->data_ptr = nullptr;

    _this->init(0, 0, Image::NoFormat);
}

#ifdef QT_PRESENT
Image::Image(QImage img, std::initializer_list<SourceID> sources)
    : _this(new ImagePrivate())
{
    _this_base.reset(_this);
    this->initSources(sources);

    enum Image::Format f;
    int cf = -1;

    switch(img.format())
    {
        case QImage::Format_RGB555: f = Image::RGB555; break;
        case QImage::Format_RGB888: f = Image::RGB888; break;
        case QImage::Format_Grayscale8: f = Image::Gray8; cf = CV_8UC1; break;
        default: f = Image::NoFormat; break;
    }

    _this->is_self_managed = false;
    _this->qt_img = img;

    // Now things are getting ugly, but Qt fights hard to force us to make a copy
    _this->data_ptr = const_cast<unsigned char*>(_this->qt_img.constBits());

#ifdef OPENCV_PRESENT
    _this->cv_img = cv::Mat(img.height(), img.width(), cf, _this->data_ptr);
#endif

    _this->init(img.width(), img.height(), f);
}
#endif

#ifdef OPENCV_PRESENT
Image::Image(cv::Mat img, std::initializer_list<SourceID> sources)
    : _this(new ImagePrivate())
{
    _this_base.reset(_this);
    this->initSources(sources);

    enum Image::Format f;

    // Be very careful when using OpenCV images in color mode! They use BGR, not RGB!
    switch(img.channels())
    {
        case 1: f = Image::Gray8; break;
        case 3: f = Image::BGR_CV; break;
        default: f = Image::NoFormat; break;
    }

    _this->is_self_managed = false;
    _this->cv_img = img;
    _this->data_ptr = _this->cv_img.data;

#ifdef QT_PRESENT
    QImage::Format qf = QImage::Format_Invalid;
    switch(img.channels())
    {
        case 1: qf = QImage::Format_Grayscale8; break;
        default: break;
    }
    _this->qt_img = QImage(img.data, img.cols, img.rows, qf);
#endif

    _this->init(img.cols, img.rows, f);
}
#endif

int Image::width() const
{
    return _this->w;
}

int Image::height() const
{
    return _this->h;
}

Image::Format Image::format() const
{
    return _this->f;
}

int Image::bitsPerPixel() const
{
    return _this->bits;
}

int Image::bytesPerPixel() const
{
    return _this->bytes;
}

int Image::dataLength() const
{
    return _this->len;
}

const unsigned char *Image::data() const
{
    return _this->data_ptr;
}

#ifdef QT_PRESENT
const QImage Image::toQt()
{
    return _this->qt_img;
}
#endif

const cv::_InputArray Image::toCv()
{
    return cv::_InputArray(_this->cv_img);
}

Image::Image(bool, std::initializer_list<SourceID> sources)
    : _this(new ImagePrivate())
{
    _this_base.reset(_this);
    this->initSources(sources);
}

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "gui/image_widget.h"
StreamWidget *Image::initWidget(OutputPrivate *out)
{
    return new ImageWidget(out);
}
#endif
