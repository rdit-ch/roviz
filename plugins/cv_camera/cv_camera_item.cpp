
#include "cv_camera_item.h"

CvCameraItem::CvCameraItem()
    : RovizItem("CvCamera")
{
    ROVIZ_INIT_ITEM(CvCamera);

    this->width_list =
    {
        1920,
        1280,
        640
    };

    this->height_list =
    {
        1080,
        720,
        480
    };

    this->output = this->addOutput<Image>("Camera Output");

    this->conf_res = this->addConfig<std::vector<std::string> >
                ("Resolution",
                 2,
                 {
                     "1920x1080",
                     "1280x720",
                     "640x480"
                 },
                 true);

    // TODO Make that safer
    this->conf_cam_id = this->addConfig<int>("Camera", 0, 0, 1000);
}

CvCameraItem::~CvCameraItem()
{
    this->stop();
}

void CvCameraItem::thread()
{
    cv::Mat frame;

    this->cap.open(this->conf_cam_id.value());
    if(!this->cap.isOpened())
        return;

    // TODO Use resolution

    while(this->wait())
    {
        this->cap >> frame;
        this->output.pushOut(Image(frame));
    }
}

void CvCameraItem::stopped()
{
    this->cap.release();
}
