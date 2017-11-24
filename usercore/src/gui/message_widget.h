#ifndef MESSAGE_WIDGET_H
#define MESSAGE_WIDGET_H

#include <QObject>
#include <QTreeWidget>
#include "gui/stream_widget.h"
#include "streams/message.h"

namespace roviz
{

class MessageWidget : public QTreeWidget, public StreamWidget
{
Q_OBJECT

public:
    explicit MessageWidget(OutputPrivate *out);
    ~MessageWidget() = default;

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

signals:
    /**
     * @brief Signal that is emitted when a new message arrives
     * @param msg The message
     *
     * All GUI operations have to happen in the GUI thread, which is why this
     * signal is needed.
     */
    void newObjectSignal(Message msg);

private slots:
    /**
     * @brief Slot that is called when a new message arrives
     * @param msg The message
     *
     * All GUI operations have to happen in the GUI thread, which is why this
     * slot is needed.
     */
    void newObjectSlot(Message msg);
};

}

#endif // MESSAGE_WIDGET_H
