
#include "canny_item.h"

CannyItem::CannyItem()
    : RovizItem("Canny")
{
    ROVIZ_INIT_ITEM(Canny);

    this->input = this->addInput<Image>("Input");
    this->output = this->addOutput<Image>("Output");
    this->trim_thres = this->addTrim("Threshold 1", 20, 1, 100, true);
    this->trim_ratio = this->addTrim("Ratio", 3, 1, 10, 0.1);
}

CannyItem::~CannyItem()
{
    this->stop();
}

void CannyItem::thread()
{
    while(this->input.waitForInput())
    {
        cv::Mat out;
        int t1, t2;
        Image in = this->input.next();

        if(in.format() != Image::Gray8)
            continue;

        t1 = this->trim_thres.value();
        t2 = t1 * this->trim_ratio.value();
        cv::Canny(in.toCv(), out, t1, t2);
        this->output.pushOut(Image(out));
    }
}
