
#include "sobel_item.h"

SobelItem::SobelItem()
    : PortableItem("Sobel")
{
    PORTABLE_INIT(Sobel);

    this->input = this->addImageInput("Input");
    this->output = this->addImageOutput("Output");
}

SobelItem::~SobelItem()
{
    this->stop();
}

void SobelItem::thread()
{
    while(this->waitForImage(this->input))
    {
        cv::Mat out, grad_x, grad_y, abs_grad_x, abs_grad_y;
        PortableImage in = this->nextImage(this->input);

        if(in.format() != PortableImage::Gray8)
            continue;

        // Gradient X
        Sobel(in.toCv(), grad_x, CV_16S, 1, 0, 3);
        convertScaleAbs(grad_x, abs_grad_x);

        // Gradient Y
        Sobel(in.toCv(), grad_y, CV_16S, 0, 1, 3);
        convertScaleAbs(grad_y, abs_grad_y);

        // Total Gradient (approximate)
        addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, out);

        this->pushImageOut(PortableImage(out), this->output);
    }
}
