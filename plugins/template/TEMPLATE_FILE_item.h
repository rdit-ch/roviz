#ifndef TEMPLATE_UPPER_ITEM_H
#define TEMPLATE_UPPER_ITEM_H

#include "portable/portable_item.h"
#include "portable/portable_image_mutable.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

class TEMPLATE_CLASSItem : public PortableItem
{
    Q_OBJECT

public:
    PORTABLE_INVOKABLE TEMPLATE_CLASSItem();
    ~TEMPLATE_CLASSItem();

protected:
    void thread(void) override;

private:
    ImageInput input;
    ImageOutput output;
};

#endif // TEMPLATE_UPPER_ITEM_H
