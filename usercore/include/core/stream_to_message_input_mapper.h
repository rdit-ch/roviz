#ifndef STREAMTOMESSAGEINPUTMAPPER_H
#define STREAMTOMESSAGEINPUTMAPPER_H

#include <QObject>
#include "item/item_input.h"
#include "portable/portable_image.h"
#include "portable/portable_item_global.h"
#include "core/message.h"

/**
 * @brief Maps the signal that a new message is ready to the right input
 *
 * \ingroup robot_framework
 */
class StreamToMessageInputMapper : public QObject
{
    Q_OBJECT

public:
    ItemInput *input;
    QMetaObject::Connection conn1, conn2;

    explicit StreamToMessageInputMapper(QObject *parent = nullptr);
    ~StreamToMessageInputMapper();

public slots:
    void inputMapper(Message message);

signals:
    void newMessage(void *input, Message message);
};

#endif // STREAMTOMESSAGEINPUTMAPPER_H
