#ifndef IMAGESTREAM_H
#define IMAGESTREAM_H

#include <QObject>
#include "item/abstract_item.h"
#include "portable/portable_image.h"
#include "helper/startup_helper.h"
#include "core/robot_core.h"
#include "core/abstract_robot_item.h"

/**
 * @brief Delivers PortableImage objects from one item to another
 *
 * \ingroup robot_framework
 */
class ROBOTCORE_EXPORT ImageStream : public QObject
{
    Q_OBJECT

public:
    static void init(void);

    ImageStream(QObject *parent = nullptr);
    ~ImageStream();

signals:
    /**
     * @brief The output produced a new image
     * @param img The new image
     */
    void newImage(const PortableImage img);
};

#endif // IMAGESTREAM_H
