#ifndef CVCAMERA_ITEM_H
#define CVCAMERA_ITEM_H

#include "portable/portable_item.h"
#include "portable/portable_image_mutable.h"
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

class CvCameraItem : public PortableItem
{
    Q_OBJECT

public:
    PORTABLE_INVOKABLE CvCameraItem();
    ~CvCameraItem();

protected:
    void thread(void) override;
    void stopped(void) override;

private:
    void *output;
    int cam_id;
    cv::VideoCapture cap;
    std::vector<std::string> res_list;
    std::vector<int> width_list, height_list;
    int res_index;
};

#endif // CVCAMERA_ITEM_H
