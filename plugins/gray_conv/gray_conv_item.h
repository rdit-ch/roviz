#ifndef GRAYCONV_ITEM_H
#define GRAYCONV_ITEM_H

#include "core/roviz_item.h"
#include "streams/image_m.h"

/**
 * @brief Converts an RGB image to grayscale
 *
 * \ingroup robot_plugins
 */
class GrayConvItem : public RovizItemParallelizable
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
    Output<Image> output;
    Input<Image> input;

    static Image fromRGB(Image in, int depth);
    static Image fromRGB555(Image in);
    static Image fromRGB888(Image in);
    static Image fromYUV422(Image in);
    static Image fromYUV422_Flipped(Image in);
};

#endif // GRAYCONV_ITEM_H
