
#include "gray_conv_item.h"

GrayConvItem::GrayConvItem()
    : roviz::Item("GrayConv")
{
    ROVIZ_INIT_ITEM(GrayConv);

    this->input = this->addInput<roviz::Image>("RGB roviz::Input");
    this->output = this->addOutput<roviz::Image>("Grayscale roviz::Output");
}

GrayConvItem::~GrayConvItem()
{
    this->stop();
}

void GrayConvItem::pre_thread()
{
}

void GrayConvItem::thread()
{
    roviz::Image in;
#ifdef OPENCV_PRESENT
    cv::Mat out;
#endif

    while(this->input.waitForInput())
    {
        in = this->input.next();

        switch(in.format())
        {
            case roviz::Image::RGB888:

                this->output.pushOut(GrayConvItem::fromRGB888(in));
                break;

            case roviz::Image::RGB555:

                this->output.pushOut(GrayConvItem::fromRGB555(in));
                break;

            case roviz::Image::YUV422:

                this->output.pushOut(GrayConvItem::fromYUV422(in));
                break;

            case roviz::Image::YUV422_Flipped:

                this->output.pushOut(GrayConvItem::fromYUV422_Flipped(in));
                break;

            case roviz::Image::BGR_CV:

#ifdef OPENCV_PRESENT
                cv::cvtColor(in.toCv(), out, CV_BGR2GRAY);
                this->output.pushOut(roviz::Image(out));
#endif
                break;

            case roviz::Image::Gray8:

                this->output.pushOut(in);
                break;

            default:
                break;
        }
    }
}

roviz::Image GrayConvItem::fromRGB(roviz::Image in, int depth)
{
    int r, g, b;
    int y;
    unsigned char *dst;

    roviz::ImageMutable out(in.width(),
                             in.height(),
                             roviz::Image::Gray8,
                             {in.id()});

    const unsigned char *src = in.data();
    const unsigned char *end = src + in.dataLength();
    dst = out.data();

    // Reference: http://computer-vision-talks.com/2011-02-08-a-very-fast-bgra-to-grayscale-conversion-on-iphone/
    // About twice as fast as the floating point version!
    // NOTE If we ever have to seriously use this on an ARM, use NEON (~six times faster!)
    while(src != end)
    {
        b = *src++; // Load blue
        g = *src++; // Load green
        r = *src++; // Load red

        // Build weighted average:
        y = (r * 77) + (g * 151) + (b * 28);

        // Undo the scale by 256 and write to memory:
        *dst++ = (y >> depth);
    }

    return out;
}

roviz::Image GrayConvItem::fromRGB555(roviz::Image in)
{
    return GrayConvItem::fromRGB(in, 5);
}

roviz::Image GrayConvItem::fromRGB888(roviz::Image in)
{
    return GrayConvItem::fromRGB(in, 8);
}

roviz::Image GrayConvItem::fromYUV422(roviz::Image in)
{
    unsigned char *dst;

    roviz::ImageMutable out(in.width(),
                             in.height(),
                             roviz::Image::Gray8,
                             {in.id()});

    const unsigned char *src = in.data();
    const unsigned char *end = src + in.dataLength();
    dst = out.data();

    while(src < end)
    {
        *dst++ = *src;
        src += 2;
    }

    return out;
}

roviz::Image GrayConvItem::fromYUV422_Flipped(roviz::Image in)
{
    unsigned char *dst;

    roviz::ImageMutable out(in.width(),
                             in.height(),
                             roviz::Image::Gray8,
                             {in.id()});

    const unsigned char *end = in.data();
    const unsigned char *src = end + in.dataLength() - 2;
    dst = out.data();

    // Unflipping the image while converting
    while(src > end)
    {
        *dst++ = *src;
        src -= 2;
    }

    return out;
}
