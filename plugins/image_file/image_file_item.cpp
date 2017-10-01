
#include "image_file_item.h"

ImageFileItem::ImageFileItem()
    : RovizItem("ImageFile")
{
    ROVIZ_INIT_ITEM(ImageFile);

    this->output = this->addOutput<Image>("Output");

    this->conf_paths = this->addConfig<FilePath>(
                "Path to the input images",
                {""},
                FilePath::ExistingFile,
                "Image files (*.jpg *.png *.bmp);;All files (*)",
                true);

    this->conf_delay = this->addConfig<int>("Delay between images (ms)", 0, 0, std::numeric_limits<int>::max());
    this->conf_repeat = this->addConfig<bool>("Repeat when all images were processed", false, false);
    this->conf_gray = this->addConfig<bool>("Load image as grayscale", false, false);
}

ImageFileItem::~ImageFileItem()
{
    this->stop();
}

void ImageFileItem::thread()
{
    std::list<Image> images;
    int load_gray, delay;
    bool repeat;

    repeat = this->conf_repeat.value();
    load_gray = this->conf_gray.value() ? CV_LOAD_IMAGE_GRAYSCALE : CV_LOAD_IMAGE_COLOR;
    delay = this->conf_delay.value();

    for(const auto &path : this->conf_paths.value())
    {
        this->wait();

        Image img(cv::imread(path, load_gray));
        if(img.format() == Image::NoFormat)
            continue;

        this->output.pushOut(img);

        if(repeat)
            images.push_back(img);

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }

    if(repeat)
    {
        while(this->wait())
        {
            for(const auto &img : images)
                this->output.pushOut(img);

            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }
    }
}
