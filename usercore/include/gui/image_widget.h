#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <QResizeEvent>
#include "core/robot_core.h"
#include "portable/portable_image.h"

/**
 * @brief A widget to show images
 *
 * This widget automatically scales the image it is supposed to display to the
 * correct size.
 *
 * \ingroup robot_framework
 */
class ROBOTCORE_EXPORT ImageWidget : public QLabel
{
Q_OBJECT

public:
    ImageWidget(QWidget *parent = nullptr);

    /**
     * @brief Set the image that the widget should display
     * @param img
     */
    void setImage(const PortableImage img);

    /**
     * @brief Reset the widget to make it show the default image again
     */
    void reset(void);

protected:
    void resizeEvent(QResizeEvent *) override;

private:
    QPixmap original, default_pix;
    PortableImage image;

private slots:
    void setPixmapSlot(QImage img);

signals:
    void setPixmapSignal(QImage img);
};

#endif // IMAGEWIDGET_H
