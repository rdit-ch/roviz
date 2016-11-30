#ifndef SUBTRACTOR_ITEM_H
#define SUBTRACTOR_ITEM_H

#include "portable/portable_item.h"
#include "portable/portable_image_mutable.h"

/**
 * @brief Subtracts two images
 *
 * \ingroup robot_plugins
 */
class SubtractorItem : public PortableItem
{
    Q_OBJECT

public:
    PORTABLE_INVOKABLE SubtractorItem();
    ~SubtractorItem();

protected:
    void starting(void) override;
    void thread(void) override;

private:
    void *input1, *input2;
    void *output;
};

#endif // SUBTRACTOR_ITEM_H
