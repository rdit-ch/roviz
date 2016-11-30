
#include "canny_item.h"

CannyItem::CannyItem()
    : PortableItem("Canny")
{
    PORTABLE_INIT(Canny);

    this->input = this->addImageInput("Input");
    this->output = this->addImageOutput("Output");
    this->thres = this->addTrim("Threshold 1", 1, 100, 100);
    this->ratio = this->addTrim("Ratio", 1, 10, 100);
}

CannyItem::~CannyItem()
{
    this->stop();
}

void CannyItem::thread()
{
    while(this->waitForImage(this->input))
    {
        cv::Mat out;
        int t1, t2;
        PortableImage in = this->nextImage(this->input);

        if(in.format() != PortableImage::Gray8)
            continue;

        t1 = this->trimValue(thres);
        t2 = t1 * this->trimValue(ratio);
        cv::Canny(in.toCv(), out, t1, t2);
        this->pushImageOut(PortableImage(out), this->output);
    }
}
