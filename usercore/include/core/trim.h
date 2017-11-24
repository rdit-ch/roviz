#ifndef TRIM_H
#define TRIM_H

#include <memory>
#include "core/export_handling.h"
#include "core/trim_impl.h"

namespace roviz
{

class Item;

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
class ROVIZ_EXPORT Trim
{
COPY_DELETE(Trim)
MOVE_DEFAULT(Trim)

public:
    // We need this to allow the construction at runtime with addTrim()
    Trim() = default;
    ~Trim() = default;

    /**
     * @brief See RovizItem::addTrim
     */
    explicit Trim(TrimImpl *impl);

    /**
     * @return The current value of the Trim
     */
    double value(void) const;

private:
    std::unique_ptr<TrimImpl> impl;
};

}

#endif // TRIM_H
