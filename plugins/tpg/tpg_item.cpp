
// This is a simulation only item
#ifndef PORTABLE_EXPORT

#include "tpg_item.h"

TPGItem::TPGItem()
    : RovizItemNoExport("Test Pattern Generator")
{
    ROVIZ_INIT_ITEM(TPG);

    this->test_pattern.load(":/test_pattern.png");
    this->test_pattern = this->test_pattern.convertToFormat(QImage::Format_RGB888);

    this->output = this->addOutput<Image>("Test Pattern Output");
    this->trim = this->addTrim("FPS", 1, 120, 0,
        [this](double value)
        {
            std::lock_guard<std::mutex> g(this->mutex());

            this->timeout = 1000 / value;
            this->timer.stop();
            this->timer_expired = false;
            this->timer.start(this->timeout);
        });

    connect(&this->timer, &QTimer::timeout,
            this, &TPGItem::timerExpired,
            Qt::QueuedConnection);
}

TPGItem::~TPGItem()
{
    this->stop();
}

void TPGItem::starting()
{
    this->timeout = 1000 / this->trim.value();
    this->timer_expired = false;
    this->timer.start(this->timeout);
}

void TPGItem::thread()
{
    double f = 0.0;
    unsigned char *dst;

    if(this->test_pattern.isNull())
        return;

    while(this->waitForCond([this]{return this->timer_expired;}))
    {
        this->mutex().lock();
        this->timer_expired = false;
        this->mutex().unlock();

        const unsigned char *src = this->test_pattern.constBits();
        ImageMutable out_img = ImageMutable(this->test_pattern.width(),
                                     this->test_pattern.height(),
                                     Image::RGB888);
        dst = out_img.data();

        for(qint32 i = 0; i < this->test_pattern.byteCount(); i++)
        {
            *dst = f * *src;
            src++;
            dst++;
        }

        f += 0.03;
        if(f > 1.0)
            f = 0.0;

        this->pushOut(out_img, this->output);
    }
}

void TPGItem::timerExpired()
{
    std::lock_guard<std::mutex> g(this->mutex());

    this->timer_expired = true;
    this->wake();
}

#endif
