#ifndef FRAMEDELAYER_ITEM_H
#define FRAMEDELAYER_ITEM_H

#include "portable/portable_item.h"
#include "portable/portable_image_mutable.h"
#include <queue>

/**
 * @brief Delays incoming frames for some time before outputting them again
 *
 * \ingroup robot_plugins
 */
class FrameDelayerItem : public PortableItem
{
    Q_OBJECT

public:
    PORTABLE_INVOKABLE FrameDelayerItem();
    ~FrameDelayerItem();

protected:
    void starting(void) override;
    void thread(void) override;
    void trimChanged(void *trim, int value);

private:
    void *input;
    void *output;
    void *delay_trim;
    std::queue<PortableImage> queue;
    unsigned int delay;
    std::mutex mtx;
};

#endif // FRAMEDELAYER_ITEM_H
