
#include "canny_item.h"

CannyItem::CannyItem()
    : roviz::Item("Canny")
{
    ROVIZ_INIT_ITEM(Canny);

    this->input = this->addInput<roviz::Image>("Input");
    this->output = this->addOutput<roviz::Image>("Output");
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
        roviz::Image in = this->input.next();

        if(in.format() != roviz::Image::Gray8)
            continue;

        t1 = this->trim_thres.value();
        t2 = t1 * this->trim_ratio.value();
        cv::Canny(in.toCv(), out, t1, t2);
        this->output.pushOut(roviz::Image(out));
    }
}
