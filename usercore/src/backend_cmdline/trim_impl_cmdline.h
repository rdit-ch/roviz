#ifndef TRIM_BASE_CMDLINE_H
#define TRIM_BASE_CMDLINE_H

#include "core/export_handling.h"
#include "core/trim_impl.h"

/**
 * @brief Trim implementation for the Cmdline backend
 *
 * For this backend, a trim is a constand value and cannot
 * change once it's set.
 *
 * \sa TrimImpl
 */
class TrimImplCmdline : public TrimImpl
{
COPY_DELETE(TrimImplCmdline)
MOVE_DELETE(TrimImplCmdline)

public:
    TrimImplCmdline() = default;
    ~TrimImplCmdline() = default;

    /**
     * @brief Get the value of the Trim
     * @return The value
     *
     * \sa setValue
     */
    double value(void) override;

    /**
     * @brief Set the value of the Trim
     * @param val The value
     *
     * \sa value
     */
    void setValue(double val);

private:
    double val;
};

#endif // TRIM_BASE_CMDLINE_H
