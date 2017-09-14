
#include "message_widget.h"
#include "streams/message.h"

void MessageWidget::newObject(StreamObject obj)
{
    Message msg(obj);

    for(const auto &entry : msg)
    {

}
}

void MessageWidget::reset()
{
    this->clear();
}

QWidget *MessageWidget::qwidget()
{
    return this;
}
