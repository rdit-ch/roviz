#ifndef TIG_ITEM_H
#define TIG_ITEM_H

#include "portable/portable_item.h"
#include "portable/portable_image_mutable.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

class TIGItem : public PortableItem
{
    Q_OBJECT

public:
    PORTABLE_INVOKABLE TIGItem();
    ~TIGItem();

protected:
    void thread(void) override;

private:
    void *output;
    PortableImage img;
    std::string img_path;
    bool is_gray;
};

#endif // TIG_ITEM_H
