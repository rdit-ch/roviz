#ifndef GRAYCONV_ITEM_H
#define GRAYCONV_ITEM_H

#include "core/roviz_item.h"
#include "streams/image_m.h"

/**
 * @brief Converts an RGB image to grayscale
 *
 * \ingroup robot_plugins
 */
class GrayConvItem : public roviz::Item
{
#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
    Q_OBJECT
#endif

public:
    ROVIZ_INVOKABLE GrayConvItem();
    ~GrayConvItem();

protected:
    void pre_thread(void) override;
    void thread(void) override;

private:
    roviz::Output<roviz::Image> output;
    roviz::Input<roviz::Image> input;

    static roviz::Image fromRGB(roviz::Image in, int depth);
    static roviz::Image fromRGB555(roviz::Image in);
    static roviz::Image fromRGB888(roviz::Image in);
    static roviz::Image fromYUV422(roviz::Image in);
    static roviz::Image fromYUV422_Flipped(roviz::Image in);
};

#endif // GRAYCONV_ITEM_H
