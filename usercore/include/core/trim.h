#ifndef TRIM_H
#define TRIM_H

#include <string>
#include <functional>
#include "core/export_handling.h"
#include ROVIZ_TRIM_BASE_INCLUDE

class RovizItem;

/**
 * @brief A value that can be trimmed at runtime
 *
 * A Trim is a value that can be adjusted at runtime. If you're using the
 * itemframework as a backend, this will be implemented with sliders.
 *
 * Do not use this class directly, always use RovizItem::addTrim!
 *
 * \sa RovizItem
 * \sa Config
 */
class ROVIZ_EXPORT_CLASS Trim : public TrimBase
{
public:
    Trim() = default;

    /**
     * @brief See RovizItem::addTrim
     */
    Trim(RovizItem *item, std::string name, double min, double max, int steps, bool logarithmic, std::function<void (double)> notifier_func);
    ~Trim() = default;

    // Don't allow copies
    Trim(const Trim &trim) = delete;
    Trim &operator=(const Trim &config) = delete;

    // Allow moving
    Trim(Trim &&trim);
    Trim &operator=(Trim &&trim);

    /**
     * @return The current value of the Trim
     */
    double value(void) const override;
};

#endif // TRIM_H
