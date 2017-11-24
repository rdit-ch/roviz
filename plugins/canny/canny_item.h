#ifndef CANNY_ITEM_H
#define CANNY_ITEM_H

#include "core/roviz_item.h"
#include "streams/image_m.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

class CannyItem : public roviz::Item
{
#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
    Q_OBJECT
#endif

public:
    ROVIZ_INVOKABLE CannyItem();
    ~CannyItem();

protected:
    void thread(void) override;

private:
    roviz::Input<roviz::Image> input;
    roviz::Output<roviz::Image> output;
    roviz::Trim trim_thres, trim_ratio;
};

#endif // CANNY_ITEM_H
