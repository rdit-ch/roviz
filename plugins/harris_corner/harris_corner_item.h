#ifndef HARRISEDGE_ITEM_H
#define HARRISEDGE_ITEM_H

#include "core/roviz_item.h"
#include "streams/image_m.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

class HarrisCornerItem : public RovizItem
{
#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
    Q_OBJECT
#endif

public:
    ROVIZ_INVOKABLE HarrisCornerItem();
    ~HarrisCornerItem();

protected:
    void thread(void) override;

private:
    Input<Image> input;
    Output<Sparse<Point2D> > output;
    Trim trim_block_size, trim_aperture_size, trim_threshold, trim_k_param;
};

#endif // HARRISEDGE_ITEM_H
