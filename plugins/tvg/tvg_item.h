#ifndef TVG_ITEM_H
#define TVG_ITEM_H

#include "config/config.h"
#include "core/roviz_item.h"
#include "streams/image_m.h"
#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include <ctime>
#include <thread>

class TVGItem : public RovizItem
{
#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
    Q_OBJECT
#endif

public:
    ROVIZ_INVOKABLE TVGItem();
    ~TVGItem();

protected:
    void thread(void) override;

private:
    Output<Image> output;
    Config<FilePath> conf_vid_path;
};

#endif // TVG_ITEM_H
