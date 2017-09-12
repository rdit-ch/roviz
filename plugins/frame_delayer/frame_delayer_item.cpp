
#include "frame_delayer_item.h"

FrameDelayerItem::FrameDelayerItem()
    : RovizItem("FrameDelayer")
{
    ROVIZ_INIT_ITEM(FrameDelayer);

    this->input = this->addInput<Image>("Input");
    this->output = this->addOutput<Image>("Output");
    this->trim_delay = this->addTrim("Delay (Frames)", 1, 10);
}

FrameDelayerItem::~FrameDelayerItem()
{
    this->stop();
}

void FrameDelayerItem::thread()
{
    while(this->waitForInput(this->input))
    {
        std::this_thread::yield();
        std::lock_guard<std::mutex> g(this->mtx);

        this->queue.push(this->newest<Image>(this->input));
        if(this->trim_delay.value() >= this->queue.size())
            continue;

        this->pushOut(this->queue.front(), this->output);
        this->queue.pop();
    }
}

void FrameDelayerItem::trimChanged(void *, int)
{
    std::lock_guard<std::mutex> g(this->mtx);

    // Clear queue
    std::queue<Image>().swap(this->queue);
}
