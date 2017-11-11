
#include "gui/sparse_widget.h"

#include <QPaintEvent>
#include <thread>
#include "core/template_decl.h"
#include "streams/sparse.h"

SparseWidget::SparseWidget(std::function<void (SparseWidget *)> draw_func, StreamObject default_item, std::function<Image (StreamObject)> image_fn, OutputPrivate *out)
    : ImageWidget(out),
      sparse_obj(default_item),
      def_item(default_item),
      draw_fn(draw_func),
      image_fn(image_fn)
{
}

void SparseWidget::newObject(StreamObject obj)
{
    this->sparse_obj = obj;
    this->ImageWidget::newObject(this->image_fn(obj));
}

void SparseWidget::resetWidget()
{
    this->sparse_obj = def_item;
    this->ImageWidget::resetWidget();
}

template<class T>
void SparseWidget::draw()
{
}

template<>
void SparseWidget::draw<Point2D>()
{
    Sparse<Point2D> sparse = Sparse<Point2D>(this->sparse_obj);
    QPainter painter(this);

    for(const auto &point : sparse)
    {
        this->updatePenColor(painter, point);
        painter.drawRect(xTF(point.x - (POINT_RECT_SIZE / 2)),
                         yTF(point.y - (POINT_RECT_SIZE / 2)),
                         POINT_RECT_SIZE, POINT_RECT_SIZE);
    }
}

template<>
void SparseWidget::draw<Point2F>()
{
    Sparse<Point2F> sparse = Sparse<Point2F>(this->sparse_obj);
    QPainter painter(this);

    for(const auto &point : sparse)
    {
        this->updatePenColor(painter, point);
        painter.drawRect(QRectF(xTF(point.x - (POINT_RECT_SIZE / 2)),
                                yTF(point.y - (POINT_RECT_SIZE / 2)),
                                POINT_RECT_SIZE, POINT_RECT_SIZE));
    }
}

template<>
void SparseWidget::draw<Rect>()
{
    Sparse<Rect> sparse = Sparse<Rect>(this->sparse_obj);
    QPainter painter(this);

    for(const auto &rect : sparse)
    {
        this->updatePenColor(painter, rect);
        painter.drawRect(xTF(rect.top - (rect.width / 2)),
                         yTF(rect.left - (rect.height / 2)),
                         wTF(rect.width), hTF(rect.height));
    }
}

template<>
void SparseWidget::draw<RectF>()
{
    Sparse<RectF> sparse = Sparse<RectF>(this->sparse_obj);
    QPainter painter(this);

    for(const auto &rect : sparse)
    {
        this->updatePenColor(painter, rect);
        painter.drawRect(QRectF(xTF(rect.top - (rect.width / 2)),
                                yTF(rect.left - (rect.height / 2)),
                                wTF(rect.width), hTF(rect.height)));
    }
}

template<>
void SparseWidget::draw<Circle>()
{
    Sparse<Circle> sparse = Sparse<Circle>(this->sparse_obj);
    QPainter painter(this);

    for(const auto &circle : sparse)
    {
        this->updatePenColor(painter, circle);
        painter.drawEllipse(QPoint(xTF(circle.x), yTF(circle.y)),
                            (int)wTF(circle.r), (int)hTF(circle.r));
    }
}

template<>
void SparseWidget::draw<CircleF>()
{
    Sparse<CircleF> sparse = Sparse<CircleF>(this->sparse_obj);
    QPainter painter(this);

    for(const auto &circle : sparse)
    {
        this->updatePenColor(painter, circle);
        painter.drawEllipse(QPointF(xTF(circle.x), yTF(circle.y)),
                            wTF(circle.r), hTF(circle.r));
    }
}

void SparseWidget::paintEvent(QPaintEvent *event)
{
    std::thread th(&SparseWidget::paintThread, this, event);


    this->ImageWidget::paintEvent(event);
    this->draw_fn(this);
}

template<class T>
void SparseWidget::updatePenColor(QPainter &painter, T obj)
{
    QPen pen(SparseColor[obj.group % sizeof(SparseColor)]);
    pen.setWidth(SPARSE_LINE_WIDTH);
    painter.setPen(pen);
}

// TODO Optimize those?
double SparseWidget::xTF(double x)
{
    return this->image_rect.x() + (x * ((double)this->image_rect.width() / this->image.width()));
}

double SparseWidget::yTF(double y)
{
    return this->image_rect.y() + (y * ((double)this->image_rect.height() / this->image.height()));
}

double SparseWidget::wTF(double w)
{
    return w * ((double)this->image_rect.width() / this->image.width());
}

double SparseWidget::hTF(double h)
{
    return h * ((double)this->image_rect.height() / this->image.height());
}

void SparseWidget::paintThread(QPaintEvent *event)
{

}

void SparseWidget::paintSlot(void)
{
    QPainter painter(this);

    painter.drawImage(this->image_rect, this->image_qt);
}

#define INSTANTIATE_SPARSE_WIDGET(T) template void SparseWidget::draw<T>(void);

DO_FOR_ALL_SPARSE_TYPES(INSTANTIATE_SPARSE_WIDGET)
