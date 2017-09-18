#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QRectF>
#include <QImage>
#include <QLabel>
#include "core/export_handling.h"
#include "streams/image.h"
#include "streams/stream_object.h"
#include "gui/stream_widget.h"

class QWidget;
class QPaintEvent;
class QResizeEvent;

// TODO Use native OpenGL (maybe that? https://github.com/Myzhar/QtOpenCVViewerGl),
// implement BGR display for OpenCV, just switching to QOpenGLWidget doesn't seem to work,
// don't know why.
/**
 * @brief A widget to show images
 *
 * This widget automatically scales the image it is supposed to display to the
 * correct size.
 *
 * \sa Image
 * \sa StreamWidget
 * \sa StreamObject
 */
class ROVIZ_EXPORT ImageWidget : public QLabel, public StreamWidget
{
Q_OBJECT

public:
    explicit ImageWidget(OutputPrivate *out);
    virtual ~ImageWidget() = default;

    /**
     * @brief Called when a new image arrived
     * @param obj StreamObject representing the new image to display
     */
    void newObject(StreamObject obj) override;

    /**
     * @brief Reset the widget to make it show the default image again
     */
    void resetWidget(void) override;

    /**
     * @brief Convert this widget to a QWidget
     * @return The QWidget
     */
    QWidget *qwidget(void) override;

protected:
    /**
     * @brief Paint the widget
     * @param event The paint event
     *
     * See QWidget::paintEvent
     */
    virtual void paintEvent(QPaintEvent *event) override;

    /**
     * @brief Called on a resize event
     * @param event The resize event
     *
     * See QWidget::resizeEvent
     */
    void resizeEvent(QResizeEvent *event) override;

protected:
    QImage image_qt;
    Image image; // To keep a reference, prevents deletion
    QRectF image_rect;

    /**
     * @brief Recalculates the image dimensions after a resize
     * @param w The new width of the bounding rect
     * @param h The new height of the bounding rect
     */
    void recalcImageRect(double w, double h);
};

#endif // IMAGEWIDGET_H
