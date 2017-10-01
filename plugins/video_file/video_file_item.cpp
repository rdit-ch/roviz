
#include "video_file_item.h"

VideoFileItem::VideoFileItem()
    : RovizItem("VideoFile")
{
    ROVIZ_INIT_ITEM(VideoFile);

    this->output = this->addOutput<Image>("Output");

    this->conf_path = this->addConfig<FilePath>(
                "Path to the video",
                {""},
                FilePath::ExistingFile,
                "Video Files (*.mp4 *.mkv *.flv *.m4a *.avi);;All Files (*)",
                true);
}

VideoFileItem::~VideoFileItem()
{
    this->stop();
}

void VideoFileItem::thread()
{
    std::chrono::high_resolution_clock::time_point time_next_frame;
    cv::Mat out;
    cv::VideoCapture cap(this->conf_path.value().front());

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
