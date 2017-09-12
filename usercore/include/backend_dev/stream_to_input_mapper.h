#ifndef STREAMTOINPUTMAPPER_H
#define STREAMTOINPUTMAPPER_H

#include <QObject>
#include "core/export_handling.h"
#include "core/typedecl.h"
#include "streams/stream_object.h"

class ItemInput;

/**
 * @brief Maps the signal that a new message is ready to the right input
 *
 * \sa SharedWindow
 */
class StreamToInputMapper : public QObject
{
    Q_OBJECT

public:
    ItemInput *input;
    QMetaObject::Connection conn1, conn2;

    explicit StreamToInputMapper(QObject *parent = nullptr);
    ~StreamToInputMapper() = default;

public slots:
    /**
     * @brief Map a StreamObject to an input
     * @param obj The stream object
     *
     * Emits the newObject signal for the StreamObject and the input associated
     * to this object.
     */
    void inputMapper(StreamObject obj);

signals:
    /**
     * @brief A new object arrived at an input
     * @param obj The stream object
     * @param input The input that the stream object arrived at
     */
    void newObject(StreamObject obj, Input input);
};

#endif // STREAMTOINPUTMAPPER_H
