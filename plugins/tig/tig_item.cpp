
#include "tig_item.h"

TIGItem::TIGItem()
    : PortableItem("Test Image Generator")
{
    PORTABLE_INIT(TIG);

    this->is_gray = false;

    this->output = this->addImageOutput("Output");
    this->addConfig("Image Path", &this->img_path);
    this->addConfig("Load as grayscale", &this->is_gray);
}

TIGItem::~TIGItem()
{
    this->stop();
}

void TIGItem::thread()
{
    this->img = PortableImage(cv::imread(this->img_path,
                                         this->is_gray ?
                                             CV_LOAD_IMAGE_GRAYSCALE
                                           :
                                             CV_LOAD_IMAGE_COLOR));

    while(this->wait())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        this->pushImageOut(this->img, this->output);
    }
}
