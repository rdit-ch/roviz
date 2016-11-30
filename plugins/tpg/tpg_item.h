#ifndef TPG_H
#define TPG_H

// This is a simulation only item
#ifndef PORTABLE_EXPORT

#include <QImage>
#include <QTimer>
#include <atomic>
#include "portable/portable_item.h"
#include "portable/portable_image_mutable.h"

/**
 * @brief Test pattern generator for testing
 *
 * \ingroup robot_plugins
 */
class TPGItem : public PortableItem
{
    Q_OBJECT

public:
    PORTABLE_INVOKABLE TPGItem();
    ~TPGItem();

private:
    void starting(void) override;
    void thread(void) override;
    void trimChanged(void *trim, double value) override;

    QImage test_pattern;
    PortableImageMutable out_img;
    QTimer timer;
    int timeout;
    void *output, *trim;
    bool timer_expired;

private slots:
    void timerExpired(void);

};

#endif
#endif // TPG_H
