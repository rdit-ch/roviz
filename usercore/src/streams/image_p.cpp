
#include "streams/image_p.h"

namespace roviz
{

ImagePrivate::~ImagePrivate()
{
    if(this->is_self_managed)
        std::free(this->data_ptr);
}

void ImagePrivate::init(int w, int h, Image::Format f)
{
    this->w = w;
    this->h = h;
    this->f = f;

    switch(f)
    {
        case Image::RGB555:

            this->bits = 16;
            this->bytes = 2;
            break;

        case Image::RGB888:

            this->bits = 24;
            this->bytes = 3;
            break;

        case Image::Gray8:

            this->bits = 8;
            this->bytes = 1;
            break;

        case Image::YUV422:
        case Image::YUV422_Flipped:

            this->bits = 16;
            this->bytes = 2;
            break;

        default:
            break;
    }

    this->len = w * h * this->bytes;
}

}
