
#include "gaussian_blur_item.h"

GaussianBlurItem::GaussianBlurItem()
    : roviz::Item("GaussianBlur")
{
    ROVIZ_INIT_ITEM(GaussianBlur);

    this->input = this->addInput<roviz::Image>("Input");
    this->output = this->addOutput<roviz::Image>("Output");
    this->trim_sigma = this->addTrim("Sigma", 0, 10, 100);
    this->trim_ksize = this->addTrim("Kernel Size", 3, 1, 11, 2.);
}

GaussianBlurItem::~GaussianBlurItem()
{
    this->stop();
}

void GaussianBlurItem::thread()
{
    while(this->input.waitForInput())
    {
        cv::Mat out;
        roviz::Image img = this->input.next();
        int ksize = this->trim_ksize.value();
        double sigma = this->trim_sigma.value();
        cv::GaussianBlur(img.toCv(),
                         out,
                         cv::Size(ksize, ksize),
                         sigma, sigma);
        this->output.pushOut(roviz::Image(out, {img.id()}));
    }
}
