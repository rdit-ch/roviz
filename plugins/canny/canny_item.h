#ifndef CANNY_ITEM_H
#define CANNY_ITEM_H

#include "portable/portable_item.h"
#include "portable/portable_image_mutable.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

class CannyItem : public PortableItem
{
    Q_OBJECT

public:
    PORTABLE_INVOKABLE CannyItem();
    ~CannyItem();

protected:
    void thread(void) override;

private:
    void *input;
    void *output;
    void *thres, *ratio;
};

#endif // CANNY_ITEM_H
