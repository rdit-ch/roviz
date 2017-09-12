
#include "frame_delayer_item.h"

FrameDelayerItem::FrameDelayerItem()
    : RovizItem("FrameDelayer")
{
    ROVIZ_INIT_ITEM(FrameDelayer);

    this->input = this->addInput<Image>("Input");
    this->output = this->addOutput<Image>("Output");
    this->trim_delay = this->addTrim("Delay (Frames)", 3, 1, 10);
}

FrameDelayerItem::~FrameDelayerItem()
{
    this->stop();
}

void FrameDelayerItem::thread()
{
    while(this->input.waitForInput())
    {
        std::this_thread::yield();
        std::lock_guard<std::mutex> g(this->mtx);

        this->queue.push(this->input.newest());
        if(this->trim_delay.value() >= this->queue.size())
            continue;

        this->output.pushOut(this->queue.front());
        this->queue.pop();
    }
}

void FrameDelayerItem::trimChanged(void *, int)
{
    std::lock_guard<std::mutex> g(this->mtx);

    // Clear queue
    std::queue<Image>().swap(this->queue);
}
