
#include "message_widget.h"

#include <cstdint>
#include "core/logger.h"

namespace roviz
{

MessageWidget::MessageWidget(OutputPrivate *out)
    : QTreeWidget(nullptr), StreamWidget(out)
{
    logger->critical_if(out == nullptr, "Trying to construct an message widget with a null-output");

    QTreeWidgetItem *item = new QTreeWidgetItem({"Name", "Value"});
    this->setHeaderItem(item);
    connect(this, &MessageWidget::newObjectSignal,
            this, &MessageWidget::newObjectSlot,
            Qt::QueuedConnection);
}

void MessageWidget::newObject(StreamObject obj)
{
    Message msg(obj);

    emit this->newObjectSlot(msg);
}

void MessageWidget::resetWidget()
{
    this->clear();
}

QWidget *MessageWidget::qwidget()
{
    return this;
}

void MessageWidget::newObjectSlot(Message msg)
{
    QTreeWidgetItem *item = new QTreeWidgetItem({QString::fromStdString(msg.type()),"0x" + QString::number(reinterpret_cast<std::uintptr_t>(msg._this), 16)});

    for(const auto &entry : msg)
        item->addChild(new QTreeWidgetItem({QString::fromStdString(entry.name()), QString::fromStdString(entry.value())}));

    // We have to temporarily disable updates, because the widget will flicker
    // otherwise
    setUpdatesEnabled(false);
    this->collapseItem(this->topLevelItem(0));
    this->insertTopLevelItem(0, item);
    this->expandItem(item);
    setUpdatesEnabled(true);
}

}
