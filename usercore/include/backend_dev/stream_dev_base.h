#ifndef STREAM_DEV_BASE_H
#define STREAM_DEV_BASE_H

#include <QObject>
#include <QWidget>
#include "streams/stream_object.h"

/**
 * @brief Base class for the dev implementation of the streams
 *
 * The dev implementation of a stream needs a seperate base, because there are
 * things (like the widget) that have to be accessible without knowing the type.
 *
 * \sa Stream
 * \sa StreamDevBasePrivate
 */
class StreamDevBase : public QObject
{
Q_OBJECT

public:
    StreamDevBase() = default;
    virtual ~StreamDevBase() = default;

    /**
     * @brief Get the widget of the stream
     * @return The widget of the stream
     *
     * Each stream has a widget that shows the current state of the stream. This
     * function returns that widget.
     */
    QWidget *widget(void);

protected:
    QWidget *widget_ptr;

signals:
    /**
     * @brief A new object arrived on the stream
     * @param obj The object that arrived
     *
     * \sa StreamObject
     */
    void newObject(StreamObject obj);
};

#endif // STREAM_DEV_BASE_H
