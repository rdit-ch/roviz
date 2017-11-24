#ifndef SUBTRACTOR_ITEM_H
#define SUBTRACTOR_ITEM_H

#include "core/roviz_item.h"
#include "streams/image_m.h"

/**
 * @brief Subtracts two images
 *
 * \ingroup robot_plugins
 */
class SubtractorItem : public roviz::Item
{
#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
    Q_OBJECT
#endif

public:
    ROVIZ_INVOKABLE SubtractorItem();
    ~SubtractorItem();

protected:
    void pre_thread(void) override;
    void thread(void) override;

private:
    roviz::Input<roviz::Image> input1, input2;
    roviz::Output<roviz::Image> output;
};

#endif // SUBTRACTOR_ITEM_H
