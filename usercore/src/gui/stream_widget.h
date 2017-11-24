#ifndef STREAM_WIDGET_H
#define STREAM_WIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include "streams/stream_object.h"
#include "core/output_p.h"

namespace roviz
{

/**
 * @brief Base class for all widgets representing a StreamObject
 *
 * \sa StreamObject
 */
class StreamWidget
{
public:
    explicit StreamWidget(OutputPrivate *out);
    virtual ~StreamWidget() = default;

    /**
     * @brief Called when a new image arrived
     * @param obj StreamObject representing the new object to display
     */
    virtual void newObject(StreamObject obj) = 0;

    /**
     * @brief Reset the widget to make it show the default image again
     */
    virtual void resetWidget(void) = 0;

    /**
     * @brief Convert this widget to a QWidget
     * @return The QWidget
     */
    virtual QWidget *qwidget(void) = 0;

    /**
     * @brief Get the output associated with this widget
     * @return The output associated with this widget
     */
    OutputPrivate *output(void);

private:
    OutputPrivate *out;
};

}

#endif // STREAM_WIDGET_H
