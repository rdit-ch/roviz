#ifndef GAUSSIANBLUR_ITEM_H
#define GAUSSIANBLUR_ITEM_H

#include "portable/portable_item.h"
#include "portable/portable_image_mutable.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"

/**
 * @brief Blurs the image with a gaussian blur
 *
 * \ingroup robot_plugins
 */
class GaussianBlurItem : public PortableItem
{
    Q_OBJECT

public:
    PORTABLE_INVOKABLE GaussianBlurItem();
    ~GaussianBlurItem();

protected:
    void thread(void) override;

private:
    void *input;
    void *output;
    void *trim;
};

#endif // GAUSSIANBLUR_ITEM_H
