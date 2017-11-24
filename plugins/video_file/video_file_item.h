#ifndef VIDEOFILE_ITEM_H
#define VIDEOFILE_ITEM_H

#include "core/roviz_item.h"
#include "streams/image_m.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

class VideoFileItem : public roviz::Item
{
#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
    Q_OBJECT
#endif

public:
    ROVIZ_INVOKABLE VideoFileItem();
    ~VideoFileItem();

protected:
    void thread(void) override;

private:
    roviz::Output<roviz::Image> output;
    roviz::Config<roviz::FilePath> conf_path;
};

#endif // VIDEOFILE_ITEM_H
