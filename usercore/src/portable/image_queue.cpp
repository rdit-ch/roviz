
#include "portable/image_queue.h"

ImageQueue::ImageQueue()
{
}

void ImageQueue::push(PortableImage img)
{
    std::lock_guard<std::mutex> g(this->mtx);

    this->images.push_back(img);
}

PortableImage ImageQueue::next()
{
    std::lock_guard<std::mutex> g(this->mtx);

    PortableImage img = this->images.front();
    this->images.pop_front();

    return img;
}

PortableImage ImageQueue::newest()
{
    std::lock_guard<std::mutex> g(this->mtx);

    PortableImage img = this->images.back();
    this->images.clear();

    return img;
}

bool ImageQueue::available()
{
    std::lock_guard<std::mutex> g(this->mtx);

    return !this->images.empty();
}
