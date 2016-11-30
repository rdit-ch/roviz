
#include "gray_conv_item.h"

GrayConvItem::GrayConvItem()
    : PortableItem("GrayConv")
{
    PORTABLE_INIT(GrayConv);

    this->input = this->addImageInput("RGB Input");
    this->output = this->addImageOutput("Grayscale Output");
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
    PortableImage in;
#ifdef OPENCV_PRESENT
    cv::Mat out;
#endif

    while(this->waitForImage(this->input))
    {
        in = this->nextImage(this->input);

        switch(in.format())
        {
            case PortableImage::RGB888:

                this->pushImageOut(GrayConvItem::fromRGB888(in), this->output);
                break;

            case PortableImage::RGB555:

                this->pushImageOut(GrayConvItem::fromRGB555(in), this->output);
                break;

            case PortableImage::YUV422:

                this->pushImageOut(GrayConvItem::fromYUV422(in), this->output);
                break;

            case PortableImage::YUV422_Flipped:

                this->pushImageOut(GrayConvItem::fromYUV422_Flipped(in), this->output);
                break;

            case PortableImage::BGR_CV:

#ifdef OPENCV_PRESENT
                cv::cvtColor(in.toCv(), out, CV_BGR2GRAY);
                this->pushImageOut(out, this->output);
#endif
                break;

            case PortableImage::Gray8:

                this->pushImageOut(in, this->output);
                break;

            default:
                break;
        }
    }
}

PortableImage GrayConvItem::fromRGB(PortableImage in, int depth)
{
    int r, g, b;
    int y;
    unsigned char *dst;

    PortableImageMutable out(in.width(),
                             in.height(),
                             PortableImage::Gray8,
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

PortableImage GrayConvItem::fromRGB555(PortableImage in)
{
    return GrayConvItem::fromRGB(in, 5);
}

PortableImage GrayConvItem::fromRGB888(PortableImage in)
{
    return GrayConvItem::fromRGB(in, 8);
}

PortableImage GrayConvItem::fromYUV422(PortableImage in)
{
    unsigned char *dst;

    PortableImageMutable out(in.width(),
                             in.height(),
                             PortableImage::Gray8,
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

PortableImage GrayConvItem::fromYUV422_Flipped(PortableImage in)
{
    unsigned char *dst;

    PortableImageMutable out(in.width(),
                             in.height(),
                             PortableImage::Gray8,
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
