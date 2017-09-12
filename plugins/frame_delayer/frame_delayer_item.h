#ifndef FRAMEDELAYER_ITEM_H
#define FRAMEDELAYER_ITEM_H

#include "core/roviz_item.h"
#include "streams/image_m.h"
#include <queue>
#include <thread>

/**
 * @brief Delays incoming frames for some time before outputting them again
 *
 * \ingroup robot_plugins
 */
class FrameDelayerItem : public RovizItem
{
#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
    Q_OBJECT
#endif

public:
    ROVIZ_INVOKABLE FrameDelayerItem();
    ~FrameDelayerItem();

protected:
    void thread(void) override;
    void trimChanged(void *trim, int value);

private:
    Input<Image> input;
    Output<Image> output;
    Trim trim_delay;
    std::queue<Image> queue;
    std::mutex mtx;
};

#endif // FRAMEDELAYER_ITEM_H
