
#include "sobel_item.h"

SobelItem::SobelItem()
    : roviz::Item("Sobel")
{
    ROVIZ_INIT_ITEM(Sobel);

    this->input = this->addInput<roviz::Image>("Input");
    this->output = this->addOutput<roviz::Image>("Output");
}

SobelItem::~SobelItem()
{
    this->stop();
}

void SobelItem::thread()
{
    while(this->input.waitForInput())
    {
        cv::Mat out, grad_x, grad_y, abs_grad_x, abs_grad_y;
        roviz::Image in = this->input.next();

        if(in.format() != roviz::Image::Gray8)
            continue;

        // Gradient X
        cv::Sobel(in.toCv(), grad_x, CV_16S, 1, 0, 3);
        cv::convertScaleAbs(grad_x, abs_grad_x);

        // Gradient Y
        cv::Sobel(in.toCv(), grad_y, CV_16S, 0, 1, 3);
        cv::convertScaleAbs(grad_y, abs_grad_y);

        // Total Gradient (approximate)
        cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, out);

        this->output.pushOut(roviz::Image(out));
    }
}
