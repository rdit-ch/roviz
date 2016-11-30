
#include "tvg_item.h"

TVGItem::TVGItem()
    : PortableItem("Test Video Generator")
{
    PORTABLE_INIT(TVG);

    this->output = this->addImageOutput("Output");
    this->addConfig("Video file", &this->vid_path, CONFIG_IS_PATH);
}

TVGItem::~TVGItem()
{
    this->stop();
}

void TVGItem::thread()
{
    std::chrono::high_resolution_clock::time_point last;
    std::chrono::high_resolution_clock::duration del;
    cv::Mat out;
    cv::VideoCapture cap(this->vid_path);
    if(!cap.isOpened())
        return;

    // The video seems to be too fast, don't know why though
    std::chrono::milliseconds fdel((int)(1000 / cap.get(CV_CAP_PROP_FPS)));

    last = std::chrono::high_resolution_clock::now();
    while(this->wait())
    {
        if(!cap.read(out))
            cap.set(CV_CAP_PROP_POS_FRAMES, 0);

        this->pushImageOut(PortableImage(out), this->output);
        del = std::chrono::high_resolution_clock::now() - last;
        last = std::chrono::high_resolution_clock::now();
        if(del < fdel)
            std::this_thread::sleep_for(del);
    }
}
