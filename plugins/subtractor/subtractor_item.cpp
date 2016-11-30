
#include "subtractor_item.h"

SubtractorItem::SubtractorItem()
    : PortableItem("Subtractor")
{
    PORTABLE_INIT(Subtractor);

    this->input1 = this->addImageInput("Input 1");
    this->input2 = this->addImageInput("Input 2");
    this->output = this->addImageOutput("Output");
}

SubtractorItem::~SubtractorItem()
{
    this->stop();
}

void SubtractorItem::starting()
{
}

void SubtractorItem::thread()
{
    PortableImage in1, in2;
    unsigned char *dst;

    while(this->waitForImage(this->input1) &&
          this->waitForImage(this->input2))
    {
        // We can't use nextImage, because if one input is slow, the queue on
        // the other input will never clear
        in1 = this->newestImage(this->input1);
        in2 = this->newestImage(this->input2);

        // TODO Handle more image formats
        if(in1.format() != PortableImage::Gray8 ||
           in2.format() != PortableImage::Gray8 ||
           in1.width() != in2.width() ||
           in1.height() != in2.height())
        {
            continue;
        }

        PortableImageMutable out(in1.width(),
                                 in1.height(),
                                 PortableImage::Gray8,
                                 {in1.id(), in2.id()});

        const unsigned char *src1 = in1.data();
        const unsigned char *src2 = in2.data();
        const unsigned char *end = src1 + in1.dataLength();
        dst = out.data();

        while(src1 != end)
            *dst++ = abs((int)*src1++ - (int)*src2++);

        this->pushImageOut(out, this->output);
    }
}
