#ifndef SOBEL_ITEM_H
#define SOBEL_ITEM_H

#include "core/roviz_item.h"
#include "streams/image_m.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

class SobelItem : public RovizItem
{
    Q_OBJECT

public:
    ROVIZ_INVOKABLE SobelItem();
    ~SobelItem();

protected:
    void thread(void) override;

private:
    Input input;
    Output output;
    Trim depth, dx, dy;
};

#endif // SOBEL_ITEM_H
