
#include "portable/portable_image_p.h"

PortableImagePrivate::PortableImagePrivate(PortableImage *q)
{
    _this = q;
}

void PortableImagePrivate::init(int w, int h, PortableImage::Format f, std::initializer_list<SourceID> sources)
{
    this->w = w;
    this->h = h;
    this->f = f;

    if(sources.size() == 0)
    {
        this->id = nullptr;
    }
    else
    {
        this->id = std::make_shared<ImageSrcTreeNode>();
        this->id->sources = std::vector<SourceID>(sources);
    }

    switch(f)
    {
        case PortableImage::RGB555:

            this->bits = 16;
            this->bytes = 2;
            break;

        case PortableImage::RGB888:

            this->bits = 24;
            this->bytes = 3;
            break;

        case PortableImage::Gray8:

            this->bits = 8;
            this->bytes = 1;
            break;

        case PortableImage::YUV422:
        case PortableImage::YUV422_Flipped:

            this->bits = 16;
            this->bytes = 2;
            break;

        default:
            break;
    }

    this->len = w * h * this->bytes;
}

void PortableImagePrivate::deleter(unsigned char *target)
{
    operator delete(target);
}
