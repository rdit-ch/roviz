
#include "gaussian_blur_item.h"

GaussianBlurItem::GaussianBlurItem()
    : PortableItem("GaussianBlur")
{
    PORTABLE_INIT(GaussianBlur);

    this->input = this->addImageInput("Input");
    this->output = this->addImageOutput("Output");
    this->trim = this->addTrim("Blur Factor", 0.1, 10, 100);
}

GaussianBlurItem::~GaussianBlurItem()
{
    this->stop();
}

void GaussianBlurItem::thread()
{
    while(this->waitForImage(this->input))
    {
        cv::Mat out;
        PortableImage img = this->nextImage(this->input);
        cv::GaussianBlur(img.toCv(),
                         out,
                         cv::Size(0, 0),
                         this->trimValue(this->trim));
        this->pushImageOut(PortableImage(out, {img.id()}), this->output);
    }
}
