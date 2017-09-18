#ifndef SPARSE_WIDGET_H
#define SPARSE_WIDGET_H

#include <QPainter>
#include <functional>
#include "gui/image_widget.h"

/**
 * @brief A widget to show sparse data
 *
 * This widget is an overlay to an ImageWidget, drawing the sparse data
 * inside the base image.
 *
 * \sa Sparse
 * \sa ImageWidget
 */
class SparseWidget : public ImageWidget
{
Q_OBJECT

public:
    SparseWidget(std::function<void (SparseWidget *)> draw_func, StreamObject default_item, std::function<Image (StreamObject)> image_fn, OutputPrivate *out);
    ~SparseWidget() = default;

    /**
     * @brief Called when a new sparse object arrived
     * @param obj StreamObject representing the new sparse object to display
     */
    void newObject(StreamObject obj) override;

    /**
     * @brief Reset the widget to make it show the default image again
     */
    void resetWidget(void) override;

    /**
     * @brief Draws the widget
     *
     * Draws the widget depending on the type of the sparse object
     */
    template<class T>
    void draw(void);

protected:
    /**
     * @brief Paint the widget
     * @param event The paint event
     *
     * See QWidget::paintEvent
     *
     * \sa draw
     */
    void paintEvent(QPaintEvent *event) override;

private:
    StreamObject sparse_obj, def_item;
    std::function<void (SparseWidget *)> draw_fn;
    std::function<Image (StreamObject)> image_fn;

    template<class T>
    void updatePenColor(QPainter &painter, T obj);
    double xTF(double x);
    double yTF(double y);
    double wTF(double w);
    double hTF(double h);
};

#endif // SPARSE_WIDGET_H
