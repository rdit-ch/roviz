#ifndef IMAGE_H
#define IMAGE_H

#include <initializer_list>
#include "core/export_handling.h"
#include "streams/stream_object.h"

#ifdef QT_PRESENT
    #include <QImage>
#endif
#ifdef OPENCV_PRESENT
    #include <opencv2/core.hpp>
    #include <opencv2/imgproc.hpp>
#endif

class ImagePrivate;
class OutputPrivate;
class StreamWidget;

/**
 * @brief A portable image class with smart memory management
 *
 * This class is pseudo-const. It can be assigned, but the data cannot be
 * altered. To alter the data of an image, use ImageMutable. If you are done
 * manipulating the pixels, convert it to a Image and pass it to the receiver.
 * The receiver has no way (unless he is really nasty) to go back and alter the
 * data again. This means the image data is protected (and read-only access is
 * thread safe). This prevents that two items that receive the same image
 * manipulate each others data. You can also directly convert Qt images
 * (QImage) and OpenCV images (cv::Mat) to Images.
 *
 * \sa ImageMutable
 * \sa ImagePrivate
 */
class ROVIZ_EXPORT Image : public StreamObject
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
        YUV422_Flipped, // Rotated by 180 degrees (you probably won't use that)
        BGR_CV
    };

    /**
     * @brief Converts a StreamObject to an Image
     * @param base The StreamObject
     *
     * This is only used internally, a plugin should never need to use that.
     * Only use it if you're absolutely sure the StreamObject is in fact an
     * Image!
     */
    Image(const StreamObject &base);

    /**
     * @brief Standard constructor
     * @param sources Source tree
     *
     * Needed by some container classes. Not really useful otherwise.
     */
    Image(std::initializer_list<SourceID> sources = {});

#ifdef QT_PRESENT
    /**
     * @brief Constructs an image with the given data of a QImage
     * @param img The QImage base
     * @param sources Source tree
     *
     * This class saves a reference to that image, you can throw away the QImage
     * you gave it for initialization. Manipulating the QImage you passed this
     * class afterwards will cause a deep copy!
     */
    Image(QImage img, std::initializer_list<SourceID> sources = {});
#endif
#ifdef OPENCV_PRESENT
    /**
     * @brief Constructs an image with the given data of a cv::Mat
     * @param img The cv::Mat base
     * @param sources Source tree
     *
     * This class saves a reference to that image, you can throw away the
     * cv::Mat you gave it for initialization. Manipulating the cv::Mat you
     * passed this class afterwards will cause a deep copy!
     */
    Image(cv::Mat img, std::initializer_list<SourceID> sources = {});
#endif

    ~Image() = default;

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

#ifdef QT_PRESENT
    /**
     * @brief Convert the image to a QImage
     * @return The QImage
     *
     * The returned image is immutable.
     *
     * Do not use this functions for images in BGR/YUV format! The Qt image
     * returned will have an invalid format, because Qt doesn't support BGR/YUV!
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
     * Do not use this functions for images in RGB/YUV format! The OpenCV image
     * returned will have an invalid format, because OpenCV doesn't support
     * RGB/YUV!
     */
    const cv::_InputArray toCv(void);
#endif

protected:
    ImagePrivate *_this;

    // Used by ImageMutable
    Image(bool do_init, std::initializer_list<SourceID> sources);

// Handle the displaying of the image
#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
public:
    /**
     * @brief initWidget Returns a ImageWidget to display the image
     * @param stream The asocciated stream
     * @return The QWidget to show
     *
     * See 'How to create your own streams'
     */
    static StreamWidget *initWidget(OutputPrivate *out);
#endif
};

DECLARE_STREAM_OBJECT(Image)

#endif // IMAGE_H
