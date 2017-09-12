
#include "gray_conv_item.h"

GrayConvItem::GrayConvItem()
    : RovizItem("GrayConv")
{
    ROVIZ_INIT_ITEM(GrayConv);

    this->input = this->addInput<Image>("RGB Input");
    this->output = this->addOutput<Image>("Grayscale Output");
}

GrayConvItem::~GrayConvItem()
{
    this->stop();
}

void GrayConvItem::starting()
{
}

void GrayConvItem::thread()
{
    Image in;
#ifdef OPENCV_PRESENT
    cv::Mat out;
#endif

    while(this->waitForInput(this->input))
    {
        in = this->next<Image>(this->input);

        switch(in.format())
        {
            case Image::RGB888:

                this->pushOut(GrayConvItem::fromRGB888(in), this->output);
                break;

            case Image::RGB555:

                this->pushOut(GrayConvItem::fromRGB555(in), this->output);
                break;

            case Image::YUV422:

                this->pushOut(GrayConvItem::fromYUV422(in), this->output);
                break;

            case Image::YUV422_Flipped:

                this->pushOut(GrayConvItem::fromYUV422_Flipped(in), this->output);
                break;

            case Image::BGR_CV:

#ifdef OPENCV_PRESENT
                cv::cvtColor(in.toCv(), out, CV_BGR2GRAY);
                this->pushOut(Image(out), this->output);
#endif
                break;

            case Image::Gray8:

                this->pushOut(in, this->output);
                break;

            default:
                break;
        }
    }
}

Image GrayConvItem::fromRGB(Image in, int depth)
{
    int r, g, b;
    int y;
    unsigned char *dst;

    ImageMutable out(in.width(),
                             in.height(),
                             Image::Gray8,
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

Image GrayConvItem::fromRGB555(Image in)
{
    return GrayConvItem::fromRGB(in, 5);
}

Image GrayConvItem::fromRGB888(Image in)
{
    return GrayConvItem::fromRGB(in, 8);
}

Image GrayConvItem::fromYUV422(Image in)
{
    unsigned char *dst;

    ImageMutable out(in.width(),
                             in.height(),
                             Image::Gray8,
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

Image GrayConvItem::fromYUV422_Flipped(Image in)
{
    unsigned char *dst;

    ImageMutable out(in.width(),
                             in.height(),
                             Image::Gray8,
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
