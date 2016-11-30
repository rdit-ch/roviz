#ifndef GRAYCONV_ITEM_H
#define GRAYCONV_ITEM_H

#include "portable/portable_item.h"
#include "portable/portable_image_mutable.h"

/**
 * @brief Converts an RGB image to grayscale
 *
 * \ingroup robot_plugins
 */
class GrayConvItem : public PortableItem
{
    Q_OBJECT

public:
    PORTABLE_INVOKABLE GrayConvItem();
    ~GrayConvItem();

protected:
    void starting(void) override;
    void thread(void) override;

private:
    void *output;
    void *input;

    static PortableImage fromRGB(PortableImage in, int depth);
    static PortableImage fromRGB555(PortableImage in);
    static PortableImage fromRGB888(PortableImage in);
    static PortableImage fromYUV422(PortableImage in);
    static PortableImage fromYUV422_Flipped(PortableImage in);
};

#endif // GRAYCONV_ITEM_H
