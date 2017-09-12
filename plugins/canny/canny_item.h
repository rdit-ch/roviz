#ifndef CANNY_ITEM_H
#define CANNY_ITEM_H

#include "core/roviz_item.h"
#include "streams/image_m.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

class CannyItem : public RovizItem
{
    Q_OBJECT

public:
    ROVIZ_INVOKABLE CannyItem();
    ~CannyItem();

protected:
    void thread(void) override;

private:
    Input input;
    Output output;
    Trim trim_thres, trim_ratio;
};

#endif // CANNY_ITEM_H
