#ifndef IMAGE_MUTABLE_H
#define IMAGE_MUTABLE_H

#include "streams/image.h"

namespace roviz
{

/**
 * @brief The mutable version Image
 *
 * You can manipulate the image data in this class, but it will be always
 * converted to the non-mutable version before it is sent to an item.
 *
 * \sa Image
 */
class ROVIZ_EXPORT ImageMutable : public Image
{
COPY_DELETE(ImageMutable)
MOVE_DEFAULT(ImageMutable)

public:
    ImageMutable() = default;
#ifdef QT_PRESENT
    /**
     * @brief Constructs an image with the given data of a QImage
     * @param img The QImage base
     *
     * This class saves a reference to that image, you can throw away the QImage
     * you gave it for initialization. Manipulating the QImage you passed this
     * class afterwards will cause a deep copy!
     */
    ImageMutable(QImage img, std::initializer_list<SourceID> sources = {});
#endif
#ifdef OPENCV_PRESENT
    /**
     * @brief Constructs an image with the given data of a cv::Mat
     * @param img The cv::Mat base
     *
     * This class saves a reference to that image, you can throw away the cv::Mat
     * you gave it for initialization. Manipulating the cv::Mat you passed this
     * class afterwards will cause a deep copy!
     */
    ImageMutable(cv::Mat img, std::initializer_list<SourceID> sources = {});
#endif
    /**
     * @brief Constructs an empty image with the given size
     * @param w Width of the image
     * @param h Height of the image
     * @param f Format of the image
     */
    ImageMutable(int w, int h, enum Format f, std::initializer_list<SourceID> sources = {});
    ~ImageMutable() = default;

    /**
     * @return A pointer to the mutable pixel data
     */
    unsigned char *data(void);
};

}

#endif // IMAGE_MUTABLE_H
