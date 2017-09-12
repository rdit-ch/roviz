#ifndef TEMPLATE_UPPER_ITEM_H
#define TEMPLATE_UPPER_ITEM_H

#include "core/roviz_item.h"
#include "streams/image_m.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

class TEMPLATE_CLASSItem : public RovizItem
{
#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
    Q_OBJECT
#endif

public:
    ROVIZ_INVOKABLE TEMPLATE_CLASSItem();
    ~TEMPLATE_CLASSItem();

protected:
    void thread(void) override;

private:
    Input<Image> input;
    Output<Image> output;
};

#endif // TEMPLATE_UPPER_ITEM_H
