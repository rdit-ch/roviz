#ifndef SOBEL_ITEM_H
#define SOBEL_ITEM_H

#include "portable/portable_item.h"
#include "portable/portable_image_mutable.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

class SobelItem : public PortableItem
{
    Q_OBJECT

public:
    PORTABLE_INVOKABLE SobelItem();
    ~SobelItem();

protected:
    void thread(void) override;

private:
    void *input;
    void *output;
    void *depth, *dx, *dy;
};

#endif // SOBEL_ITEM_H
