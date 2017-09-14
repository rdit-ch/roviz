#ifndef CVCAMERA_ITEM_H
#define CVCAMERA_ITEM_H

#include "core/export_handling.h"
#include "core/roviz_item.h"
#include "config/config.h"
#include "streams/image_m.h"
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

class CvCameraItem : public RovizItem
{
#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
    Q_OBJECT
#endif

public:
    ROVIZ_INVOKABLE CvCameraItem();
    ~CvCameraItem();

protected:
    void thread(void) override;
    void stopped(void) override;

private:
    Output<Image> output;
    Config<std::vector<std::string> > conf_res;
    Config<int> conf_cam_id;
    cv::VideoCapture cap;
    std::vector<int> width_list, height_list;
    int res_index;
};

#endif // CVCAMERA_ITEM_H
