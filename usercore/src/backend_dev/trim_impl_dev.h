#ifndef TRIM_BASE_DEV_H
#define TRIM_BASE_DEV_H

#include <string>
#include <memory>
#include <functional>
#include <QMetaObject>
#include "core/export_handling.h"
#include "core/trim_impl.h"

class QLayout;
class QSlider;
class QLabel;

namespace roviz
{

class ItemBaseDev;

/**
 * @brief roviz backend for a Trim
 *
 * This class implements the slider mechanic to update the value of a Trim.
 *
 * \sa Trim
 * \sa TrimImpl
 * \sa TrimImplBaseDev
 */
class TrimImplDev : public QObject, public TrimImpl
{
Q_OBJECT

COPY_DELETE(TrimImplDev)
MOVE_DELETE(TrimImplDev)

public:
    TrimImplDev() = delete;
    ~TrimImplDev() = default;

    /**
     * @brief Constructs an implementation
     *
     * \sa Item::addTrim
     */
    TrimImplDev(ItemBaseDev *item, std::string name, double default_value, double min, double max, int steps, bool logarithmic, std::function<void (double)> notifier_func = [](double){});

    /**
     * @return The Qt layout with the sliders inside
     */
    QLayout *layout(void) const;

    /**
     * @return The current value of the trim based on the slider position.
     */
    double value(void) override;

private:
    ItemBaseDev *item;
    std::string name;
    double default_value, min, scale_factor;
    bool logarithmic;
    std::function<void (double)> notifier_func;
    double val;
    QLayout *main_layout;
    QSlider *slider;
    QLabel *label_value;
    QMetaObject::Connection load_conn;

private slots:
    /**
     * @brief Load the current state of the slider from the config.
     */
    void load(void);

    /**
     * @brief Called when the value of the slider changed.
     * @param int_value The new value of the slider
     */
    void valueChanged(int int_value);
};

}

#endif // TRIM_BASE_DEV_H
