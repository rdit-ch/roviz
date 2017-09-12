#ifndef TRIM_DEV_BASE_H
#define TRIM_DEV_BASE_H

#include <string>
#include <memory>
#include "backend_dev/trim_dev_base_p.h"
#include "core/export_handling.h"

class QLayout;
class QSlider;
class RovizItem;

/**
 * @brief roviz backend for a Trim
 *
 * This class implements the slider mechanic to update the value of a Trim.
 *
 * \sa Trim
 * \sa TrimDevBasePrivate
 */
class ROVIZ_EXPORT_CLASS TrimDevBase
{
public:
    TrimDevBase() = default;
    TrimDevBase(RovizItem *item, std::string name, double min, double max, int steps, bool logarithmic, std::function<void (double)> notifier_func = [](double){});
    virtual ~TrimDevBase() = default;

    // Don't allow copies
    TrimDevBase(const TrimDevBase &trim) = delete;
    TrimDevBase &operator=(const TrimDevBase &trim) = delete;

    // Allow moving
    TrimDevBase(TrimDevBase &&trim);
    TrimDevBase &operator=(TrimDevBase &&trim);

    /**
     * @return The Qt layout with the sliders inside
     */
    QLayout *layout(void) const;

    /**
     * @return The current value of the trim based on the slider position.
     */
    virtual double value(void) const;

signals:
    void valueChanged(double value);

private:
    std::unique_ptr<TrimDevBasePrivate> _this;
};

#endif // TRIM_DEV_BASE_H
