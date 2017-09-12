#ifndef TIG_ITEM_H
#define TIG_ITEM_H

#include "core/roviz_item.h"
#include "config/file_path.h"
#include "config/config.h"
#include "streams//image_m.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include <thread>

class TIGItem : public RovizItem
{
#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
    Q_OBJECT
#endif

public:
    ROVIZ_INVOKABLE TIGItem();
    ~TIGItem();

protected:
    void thread(void) override;

private:
    Output<Image> output;
    Image img;
    Config<bool> conf_load_grey;
    Config<FilePath> conf_path;
};

#endif // TIG_ITEM_H
