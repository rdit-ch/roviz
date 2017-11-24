
#include "subtractor_item.h"

SubtractorItem::SubtractorItem()
    : roviz::Item("Subtractor")
{
    ROVIZ_INIT_ITEM(Subtractor);

    this->input1 = this->addInput<roviz::Image>("roviz::Input 1");
    this->input2 = this->addInput<roviz::Image>("roviz::Input 2");
    this->output = this->addOutput<roviz::Image>("Output");
}

SubtractorItem::~SubtractorItem()
{
    this->stop();
}

void SubtractorItem::pre_thread()
{
}

void SubtractorItem::thread()
{
    roviz::Image in1, in2;
    unsigned char *dst;

    while(this->input1.waitForInput() &&
          this->input2.waitForInput())
    {
        // We can't use nextroviz::Image, because if one input is slow, the queue on
        // the other input will never clear
        in1 = this->input1.newest();
        in2 = this->input2.newest();

        // TODO Handle more image formats
        if(in1.format() != roviz::Image::Gray8 ||
           in2.format() != roviz::Image::Gray8 ||
           in1.width() != in2.width() ||
           in1.height() != in2.height())
        {
            continue;
        }

        roviz::ImageMutable out(in1.width(),
                         in1.height(),
                         roviz::Image::Gray8,
                         {in1.id(), in2.id()});

        const unsigned char *src1 = in1.data();
        const unsigned char *src2 = in2.data();
        const unsigned char *end = src1 + in1.dataLength();
        dst = out.data();

        while(src1 != end)
            *dst++ = abs((int)*src1++ - (int)*src2++);

        this->output.pushOut(out);
    }
}
