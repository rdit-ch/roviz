
#include "gui/image_widget.h"

ImageWidget::ImageWidget(QWidget *parent)
    : QLabel(parent)
{
    this->setMinimumSize(1, 1);
    this->setSizePolicy(QSizePolicy::Expanding,
                        QSizePolicy::Expanding);
    this->setScaledContents(false);
    this->default_pix = QPixmap(":/usercore/res/default_image.png");
    this->original = this->default_pix;
    connect(this, &ImageWidget::setPixmapSignal,
            this, &ImageWidget::setPixmapSlot);
    this->resizeEvent(nullptr);
}

void ImageWidget::resizeEvent(QResizeEvent *event)
{
    if(!this->original.isNull())
        this->setPixmap(this->original.scaled(this->size(),
                                              Qt::KeepAspectRatio));
    QLabel::resizeEvent(event);
}

void ImageWidget::setPixmapSlot(QImage img)
{
    this->original = QPixmap::fromImage(img);
    this->resizeEvent(nullptr);
}

void ImageWidget::setImage(const PortableImage img)
{
    QImage::Format f = QImage::Format_Invalid;

    switch(img.format())
    {
        case PortableImage::RGB555: f = QImage::Format_RGB555; break;
        case PortableImage::RGB888: f = QImage::Format_RGB888; break;
        case PortableImage::Gray8:  f = QImage::Format_Grayscale8; break;
        default:                      f = QImage::Format_Invalid; break;
    }

    QImage qimg(img.data(), img.width(), img.height(), f);

    // The data of the PortableImage might get deleted too early,
    // because the reference counting mechanisms of PortableImage
    // and QImage are not synchronized.
    this->image = img;

    // QPixmaps can only be managed by the gui thread
    emit this->setPixmapSignal(qimg);
}

void ImageWidget::reset()
{
    this->original = this->default_pix;
    this->resizeEvent(nullptr);
}
