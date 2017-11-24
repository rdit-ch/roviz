
#include "gui/image_widget.h"

#include <QWidget>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QPainter>
#include <iostream>
#include "core/logger.h"

namespace roviz
{

ImageWidget::ImageWidget(OutputPrivate *out)
    : QLabel(nullptr),
      StreamWidget(out),
      default_pixmap(":/usercore/res/default_image.png"),
      scale_factor(1),
      scale_pixmap(true)
{
    logger->critical_if(out == nullptr, "Trying to construct an image widget with a null-output");

    this->setMinimumSize(1, 1);
    this->setSizePolicy(QSizePolicy::Expanding,
                        QSizePolicy::Expanding);
    this->resetWidget();
}

void ImageWidget::newObject(StreamObject obj)
{
    this->image = Image(obj);
    this->pixmap = QPixmap::fromImage(this->image.toQt());

    // We only have to do this if the dimensions changed, but checking this
    // would also result in overhead and the gain is minimal.
    this->recalcImageRect(this->width(), this->height());

    this->update();
}

void ImageWidget::resetWidget()
{
    this->image = Image();
    this->pixmap = this->default_pixmap;
    this->recalcImageRect(this->width(), this->height());
    this->update();
}

QWidget *ImageWidget::qwidget()
{
    return this;
}

void ImageWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    std::lock_guard<std::mutex> g(this->mtx_pixmap);
    painter.drawPixmap(this->image_rect.topLeft(), this->pixmap_scaled);
}

void ImageWidget::resizeEvent(QResizeEvent *event)
{
    this->recalcImageRect(event->size().width(), event->size().height());
    this->update();
}

void ImageWidget::recalcImageRect(double w, double h)
{
    if(this->pixmap.isNull() || this->pixmap.width() == 0 || this->pixmap.height() == 0)
    {
        this->image_rect.setRect(0, 0, 0, 0);
        return;
    }

    double ar = static_cast<double>(this->pixmap.width()) / this->pixmap.height();

    if(w > ar * h)
        this->image_rect.setRect((w - (ar * h)) / 2, 0, ar * h, h);
    else
        this->image_rect.setRect(0, (h - (w / ar)) / 2, w, w / ar);

    this->scale_factor = w / this->pixmap.width();

    if(this->scale_pixmap)
    {
        std::lock_guard<std::mutex> g(this->mtx_pixmap);
        this->pixmap_scaled = this->pixmap.scaled(this->image_rect.size());
    }
}

}
