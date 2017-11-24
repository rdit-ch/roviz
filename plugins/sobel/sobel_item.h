#ifndef SOBEL_ITEM_H
#define SOBEL_ITEM_H

#include "core/roviz_item.h"
#include "streams/image_m.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

class SobelItem : public roviz::Item
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
    roviz::Input<roviz::Image> input;
    roviz::Output<roviz::Image> output;
};

#endif // SOBEL_ITEM_H
