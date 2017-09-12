#ifndef SOBEL_ITEM_H
#define SOBEL_ITEM_H

#include "core/roviz_item.h"
#include "streams/image_m.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

class SobelItem : public RovizItem
{
#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
    Q_OBJECT
#endif

public:
    ROVIZ_INVOKABLE SobelItem();
    ~SobelItem();

protected:
    void thread(void) override;

private:
    Input<Image> input;
    Output<Image> output;
};

#endif // SOBEL_ITEM_H
