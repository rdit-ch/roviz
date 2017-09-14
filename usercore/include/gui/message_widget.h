#ifndef MESSAGE_WIDGET_H
#define MESSAGE_WIDGET_H

#include <QObject>
#include <QTreeWidget>
#include "gui/stream_widget.h"

class MessageWidget : public QTreeWidget, public StreamWidget
{
Q_OBJECT

public:
    MessageWidget() = default;
    ~MessageWidget() = default;

    /**
     * @brief Called when a new image arrived
     * @param obj StreamObject representing the new image to display
     */
    void newObject(StreamObject obj) override;

    /**
     * @brief Reset the widget to make it show the default image again
     */
    void reset(void) override;

    /**
     * @brief Convert this widget to a QWidget
     * @return The QWidget
     */
    QWidget *qwidget(void) override;
};

#endif // MESSAGE_WIDGET_H
