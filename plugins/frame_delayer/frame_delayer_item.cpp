
#include "frame_delayer_item.h"

FrameDelayerItem::FrameDelayerItem()
    : PortableItem("FrameDelayer")
{
    PORTABLE_INIT(FrameDelayer);

    this->input = this->addImageInput("Input");
    this->output = this->addImageOutput("Output");
    this->delay_trim = this->addTrim("Delay (Frames)", 1, 10);
    this->delay = 1;
}

FrameDelayerItem::~FrameDelayerItem()
{
    this->stop();
}

void FrameDelayerItem::starting()
{
    std::lock_guard<std::mutex> g(this->mtx);

    this->delay = this->trimValue(this->delay_trim);
}

void FrameDelayerItem::thread()
{
    while(this->waitForImage(this->input))
    {
        std::this_thread::yield();
        std::lock_guard<std::mutex> g(this->mtx);

        this->queue.push(this->newestImage(this->input));
        if(this->delay >= this->queue.size())
            continue;

        this->pushImageOut(this->queue.front(), this->output);
        this->queue.pop();
    }
}

void FrameDelayerItem::trimChanged(void *, int value)
{
    std::lock_guard<std::mutex> g(this->mtx);

    this->delay = value;
    // Clear queue
    std::queue<PortableImage>().swap(this->queue);
}
