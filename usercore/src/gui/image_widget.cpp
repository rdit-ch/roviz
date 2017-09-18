
#include "gui/image_widget.h"

#include <QWidget>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QPainter>

ImageWidget::ImageWidget(OutputPrivate *out)
    : QLabel(nullptr), StreamWidget(out)
{
    this->setMinimumSize(1, 1);
    this->setSizePolicy(QSizePolicy::Expanding,
                        QSizePolicy::Expanding);
}

void ImageWidget::newObject(StreamObject obj)
{
    Image img = this->image;
    this->image = Image(obj);

    // We have to resize, when the size changes
    if(this->image.format() != Image::NoFormat &&
       (img.format() != Image::NoFormat ||
        this->image.width() != img.width() ||
        this->image.height() != img.height()))
    {
        this->recalcImageRect(this->width(), this->height());
    }

    this->image_qt = this->image.toQt();
    this->update();
}

// TODO Implement
void ImageWidget::resetWidget()
{
}

QWidget *ImageWidget::qwidget()
{
    return this;
}

void ImageWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawImage(this->image_rect, this->image_qt);
}

void ImageWidget::resizeEvent(QResizeEvent *event)
{
    if(this->image.format() == Image::NoFormat)
        return;

    this->recalcImageRect(event->size().width(), event->size().height());
    this->update();
}

void ImageWidget::recalcImageRect(double w, double h)
{
    if(this->image.width() == 0 || this->image.height() == 0)
    {
        this->image_rect.setRect(0, 0, 0, 0);
        return;
    }

    double ar = (double)this->image.width() / this->image.height();

    if(w > ar * h)
        this->image_rect.setRect((w - (ar * h)) / 2, 0, ar * h, h);
    else
        this->image_rect.setRect(0, (h - (w / ar)) / 2, w, w / ar);
}
