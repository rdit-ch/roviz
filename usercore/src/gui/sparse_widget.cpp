
#include "gui/sparse_widget.h"

#include <QPaintEvent>
#include "core/template_decl.h"
#include "streams/sparse.h"

SparseWidget::SparseWidget(std::function<void (SparseWidget *)> draw_func, StreamObject default_item, std::function<Image (StreamObject)> image_fn, OutputPrivate *out)
    : ImageWidget(out),
      sparse_obj(default_item),
      default_item(default_item),
      draw_fn(draw_func),
      image_fn(image_fn)
{
    this->scale_pixmap = false;
}

void SparseWidget::newObject(StreamObject obj)
{
    this->sparse_obj = obj;
    this->ImageWidget::newObject(this->image_fn(obj));

    this->tmp_pixmap = this->pixmap.scaled(this->image_rect.size());
    this->draw_fn(this);

    std::lock_guard<std::mutex> g(this->mtx_pixmap);
    this->pixmap_scaled = this->tmp_pixmap;
}

void SparseWidget::resetWidget()
{
    this->sparse_obj = default_item;
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
    QPainter painter(&this->tmp_pixmap);

    for(const auto &point : sparse)
    {
        this->updatePenColor(painter, point);
        painter.drawRect(QRectF(this->scale_factor * (point.x - (POINT_RECT_SIZE / 2)),
                                this->scale_factor * (point.y - (POINT_RECT_SIZE / 2)),
                                POINT_RECT_SIZE, POINT_RECT_SIZE));
    }
}

template<>
void SparseWidget::draw<Rect>()
{
    Sparse<Rect> sparse = Sparse<Rect>(this->sparse_obj);
    QPainter painter(&this->tmp_pixmap);

    for(const auto &rect : sparse)
    {
        this->updatePenColor(painter, rect);
        painter.drawRect(QRectF(this->scale_factor * (rect.top - (rect.width / 2)),
                                this->scale_factor * (rect.left - (rect.height / 2)),
                                this->scale_factor * rect.width,
                                this->scale_factor * rect.height));
    }
}

template<>
void SparseWidget::draw<Circle>()
{
    Sparse<Circle> sparse = Sparse<Circle>(this->sparse_obj);
    QPainter painter(&this->tmp_pixmap);

    for(const auto &circle : sparse)
    {
        this->updatePenColor(painter, circle);
        painter.drawEllipse(QPointF(this->scale_factor * circle.x, this->scale_factor * circle.y),
                            this->scale_factor * circle.r, this->scale_factor * circle.r);
    }
}

template<class T>
void SparseWidget::updatePenColor(QPainter &painter, T obj)
{
    QPen pen(SparseColor[obj.group % sizeof(SparseColor)]);
    pen.setWidth(SPARSE_LINE_WIDTH);
    painter.setPen(pen);
}

#define INSTANTIATE_SPARSE_WIDGET(T) template void SparseWidget::draw<T>(void);

DO_FOR_ALL_SPARSE_TYPES(INSTANTIATE_SPARSE_WIDGET)
