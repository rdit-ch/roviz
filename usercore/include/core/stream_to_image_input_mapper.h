#ifndef STREAMTOIMAGEINPUTMAPPER_H
#define STREAMTOIMAGEINPUTMAPPER_H

#include <QObject>
#include "item/item_input.h"
#include "portable/portable_image.h"

/**
 * @brief Maps the signal that a new image is ready to the right input
 *
 * \ingroup robot_framework
 */
class StreamToImageInputMapper : public QObject
{
    Q_OBJECT

public:
    ItemInput *input;
    QMetaObject::Connection conn1, conn2;

    explicit StreamToImageInputMapper(QObject *parent = nullptr);
    ~StreamToImageInputMapper();

public slots:
    void inputMapper(const PortableImage img);

signals:
    void newImage(const PortableImage img, void *in);
};

#endif // STREAMTOIMAGEINPUTMAPPER_H
