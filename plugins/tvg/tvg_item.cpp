
#include "tvg_item.h"

TVGItem::TVGItem()
    : RovizItem("Test Video Generator")
{
    ROVIZ_INIT_ITEM(TVG);

    this->output = this->addOutput<Image>("Output");

    this->conf_vid_path = this->addConfig<FilePath>(
                "Path to the video",
                {""},
                FilePath::ExistingFile,
                "All Files (*)",
                true);
}

TVGItem::~TVGItem()
{
    this->stop();
}

void TVGItem::thread()
{
    std::chrono::high_resolution_clock::time_point time_next_frame;
    cv::Mat out;
    cv::VideoCapture cap(this->conf_vid_path.value().front());

    if(!cap.isOpened())
        return;

    std::chrono::microseconds frame_delay((int)(1000000. / cap.get(CV_CAP_PROP_FPS)));

    time_next_frame = std::chrono::high_resolution_clock::now();
    while(this->wait())
    {
        if(!cap.read(out))
        {
            cap.set(CV_CAP_PROP_POS_FRAMES, 0);
            cap.read(out);
        }

        // Not just using += because that doesn't work well with pauses
        time_next_frame = std::chrono::high_resolution_clock::now() + frame_delay;
        std::this_thread::sleep_until(time_next_frame);
        this->output.pushOut(Image(out));
    }
    cap.release();
}
