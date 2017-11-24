#ifndef TPG_H
#define TPG_H

#include "core/export_handling.h"

#include <QImage>
#include <QTimer>
#include <atomic>
#include "core/roviz_item.h"
#include "streams/image_m.h"

/**
 * @brief Test pattern generator for testing
 *
 * \ingroup robot_plugins
 */
class TPGItem : public roviz::Item
{
    Q_OBJECT

public:
    ROVIZ_INVOKABLE TPGItem();
    ~TPGItem();

private:
    void pre_thread(void) override;
    void thread(void) override;

    QImage test_pattern;
    QTimer timer;
    int timeout;
    roviz::Output<roviz::Image> output;
    roviz::Trim trim_fps;
    bool timer_expired;

private slots:
    void timerExpired(void);

};

#endif // TPG_H
