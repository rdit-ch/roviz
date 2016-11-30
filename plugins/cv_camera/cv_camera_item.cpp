
#include "cv_camera_item.h"

CvCameraItem::CvCameraItem()
    : PortableItem("CvCamera")
{
    PORTABLE_INIT(CvCamera);

    this->res_list =
    {
        "1920x1080",
        "1280x720",
        "640x480"
    };

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

    this->output = this->addImageOutput("Camera Output");
    this->res_index = 0;
    this->cam_id = 0;
    this->addConfig("Resolution", this->res_list, &this->res_index);
    this->addConfig("Camera", &this->cam_id, [this](int a){return a >= 0 ? a : 0;});
}

CvCameraItem::~CvCameraItem()
{
    this->stop();
}

void CvCameraItem::thread()
{
    cv::Mat frame;

    this->cap.open(this->cam_id);
    if(!this->cap.isOpened())
        return;

    while(this->wait())
    {
        this->cap >> frame;
        emit this->pushImageOut(PortableImage(frame), this->output);
    }
}

void CvCameraItem::stopped()
{
    this->cap.release();
}
