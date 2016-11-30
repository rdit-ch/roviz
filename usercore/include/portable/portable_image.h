#ifndef PORTABLEIMAGE_H
#define PORTABLEIMAGE_H

#include <memory>
#include <initializer_list>
#include "portable/portable_item_global.h"

#ifdef QT_PRESENT
    #include <QImage>
#endif
#ifdef OPENCV_PRESENT
    #include <opencv2/core.hpp>
    #include <opencv2/imgproc.hpp>
#endif

class PortableImagePrivate;
struct ImageSrcTreeNode;

/**
 * @brief The ID and source tree of an image
 */
typedef std::shared_ptr<ImageSrcTreeNode> SourceID;

/**
 * @brief A node of the source-tree
 */
struct ImageSrcTreeNode
{
    std::vector<SourceID> sources;
};

/**
 * @brief A portable image class with smart memory management
 *
 * This class is pseudo-const. It can be assigned, but the data cannot
 * be altered. To alter the data of an image, use PortableImageMutable.
 * If you are done manipulating the pixels, convert it to a PortableImage
 * and pass it to the receiver. The receiver has no way (unless he is really
 * nasty) to go back and alter the data again. This means the image is
 * protected (and read-only access is thread safe). This prevents that two
 * items that receive the same image manipulate each others data.
 *
 * This image class also provides an ID / source-tree system. That means that
 * you can track down the exact origin of every image using a tree. An image
 * that comes from a source (e.g. a camera), will be a root node in the
 * source-tree. The current node of the tree is also a unique identifier ID
 * for this image. If you now apply a filter or transformation to the image,
 * a new image with a new ID will be created. Within this ID is also stored,
 * what the original ID of the source image was. This way, if you have a long
 * filter-chain, you can in the end still match the endresult with the very
 * first image of the chain to compare the changes the image has undergone.
 * Pointclouds, for example, also support this IDs, so you could also
 * identify the source image for a pointcloud and for example create an
 * image with it's pointcloud overlaid.
 *
 * \ingroup robot_framework
 */
class PORTABLE_EXPORT_CLASS PortableImage
{
public:

    /**
     * @brief Enum of all supported image formats
     */
    enum Format
    {
        NoFormat,
        RGB555,
        RGB888,
        Gray8,
        YUV422,
        YUV422_Flipped,
        BGR_CV
    };

    PortableImage();
#ifdef QT_PRESENT
    /**
     * @brief Constructs an image with the given data of a QImage
     * @param img The QImage base
     *
     * This class saves a reference to that image, you can throw away the QImage
     * you gave it for initialization. Manipulating the QImage you passed this
     * class afterwards will cause a deep copy!
     */
    PortableImage(QImage img, std::initializer_list<SourceID> sources = {});
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
    PortableImage(cv::Mat img, std::initializer_list<SourceID> sources = {});
#endif

    // The std::unique_ptr cannot be automatically copied
    PortableImage(const PortableImage &other);
    PortableImage &operator=(const PortableImage &other);
    virtual ~PortableImage();

    /**
     * @return The width of the image
     */
    int width(void) const;

    /**
     * @return The height of the image
     */
    int height(void) const;

    /**
     * @return The format of the image
     */
    enum Format format(void) const;

    /**
     * @return The number of bits per pixel (not per channel!)
     */
    int bitsPerPixel(void) const;

    /**
     * @return The number of bytes per pixel
     */
    int bytesPerPixel(void) const;

    /**
     * @return The lenght of the pixel data in bytes
     */
    int dataLength(void) const;

    /**
     * @return A pointer to the pixel data
     */
    const unsigned char *data(void) const;

    /**
     * @return The image ID / source-tree
     */
    SourceID id(void) const;

#ifdef QT_PRESENT
    /**
     * @brief Convert the image to a QImage
     * @return The QImage
     *
     * The returned image is immutable.
     *
     * Do not use this functions for images in BGR format! The Qt image
     * returned will have an invalid format, because Qt doesn't support BGR!
     */
    const QImage toQt(void);
#endif
#ifdef OPENCV_PRESENT
    /**
     * @brief Convert the image to an OpenCV image
     * @return The OpenCV image
     *
     * The returned image is immutable and can only be used as an input for
     * OpenCV functions.
     *
     * Do not use this functions for images in RGB format! The OpenCV image
     * returned will have an invalid format, because OpenCV doesn't support
     * RGB!
     */
    const cv::_InputArray toCv(void);
#endif

protected:
    std::unique_ptr<PortableImagePrivate> _this;
};

#endif // PORTABLEIMAGE_H
