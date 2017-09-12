#ifndef SUBTRACTOR_ITEM_H
#define SUBTRACTOR_ITEM_H

#include "core/roviz_item.h"
#include "streams/image_m.h"

/**
 * @brief Subtracts two images
 *
 * \ingroup robot_plugins
 */
class SubtractorItem : public RovizItem
{
#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
    Q_OBJECT
#endif

public:
    ROVIZ_INVOKABLE SubtractorItem();
    ~SubtractorItem();

protected:
    void starting(void) override;
    void thread(void) override;

private:
    Input<Image> input1, input2;
    Output<Image> output;
};

#endif // SUBTRACTOR_ITEM_H
