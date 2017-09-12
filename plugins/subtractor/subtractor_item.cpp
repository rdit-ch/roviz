
#include "subtractor_item.h"

SubtractorItem::SubtractorItem()
    : RovizItem("Subtractor")
{
    ROVIZ_INIT_ITEM(Subtractor);

    this->input1 = this->addInput<Image>("Input 1");
    this->input2 = this->addInput<Image>("Input 2");
    this->output = this->addOutput<Image>("Output");
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
    Image in1, in2;
    unsigned char *dst;

    while(this->waitForInput(this->input1) &&
          this->waitForInput(this->input2))
    {
        // We can't use nextImage, because if one input is slow, the queue on
        // the other input will never clear
        in1 = this->newest<Image>(this->input1);
        in2 = this->newest<Image>(this->input2);

        // TODO Handle more image formats
        if(in1.format() != Image::Gray8 ||
           in2.format() != Image::Gray8 ||
           in1.width() != in2.width() ||
           in1.height() != in2.height())
        {
            continue;
        }

        ImageMutable out(in1.width(),
                         in1.height(),
                         Image::Gray8,
                         {in1.id(), in2.id()});

        const unsigned char *src1 = in1.data();
        const unsigned char *src2 = in2.data();
        const unsigned char *end = src1 + in1.dataLength();
        dst = out.data();

        while(src1 != end)
            *dst++ = abs((int)*src1++ - (int)*src2++);

        this->pushOut(out, this->output);
    }
}
