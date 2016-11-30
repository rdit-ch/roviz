#ifndef MESSAGESTREAM_H
#define MESSAGESTREAM_H

#include <QObject>
#include "core/robot_core.h"
#include "portable/portable_item_global.h"
#include "helper/startup_helper.h"
#include "item/abstract_item.h"
#include "core/message.h"

/**
 * @brief Delivers Messages from one item to another
 *
 * \ingroup robot_framework
 */
class ROBOTCORE_EXPORT MessageStream : public QObject
{
    Q_OBJECT

public:
    static void init(void);

    MessageStream(QObject *parent = nullptr);
    ~MessageStream();

signals:
    /**
     * @brief The output produced a new message
     * @param message The new message
     */
    void newMessage(Message message);
};

#endif // MESSAGESTREAM_H
