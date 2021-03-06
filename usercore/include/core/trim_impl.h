#ifndef TRIM_IMPL_H
#define TRIM_IMPL_H

/**
 * @brief The interface of a Trim implementation
 */
class TrimImpl
{
public:
    virtual ~TrimImpl() = default;

    /**
     * @brief Get the value of the Trim
     * @return The value of the Trim
     */
    virtual double value(void) = 0;
};

#endif // TRIM_IMPL_H
