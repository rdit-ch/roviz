#ifndef IMAGEFILE_ITEM_H
#define IMAGEFILE_ITEM_H

#include "core/roviz_item.h"
#include "streams/image_m.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

class ImageFileItem : public RovizItem
{
#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
    Q_OBJECT
#endif

public:
    ROVIZ_INVOKABLE ImageFileItem();
    ~ImageFileItem();

protected:
    void thread(void) override;

private:
    Output<Image> output;
    Config<FilePath> conf_paths;
    Config<int> conf_delay;
    Config<bool> conf_repeat;
    Config<bool> conf_gray;
};

#endif // IMAGEFILE_ITEM_H
