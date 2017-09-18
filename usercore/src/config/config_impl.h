#ifndef CONFIG_IMPL_H
#define CONFIG_IMPL_H

#include "core/export_handling.h"

/**
 * @brief Base class for all config implementations
 *
 * \sa Config
 */
class ConfigImpl
{
COPY_DELETE(ConfigImpl)
MOVE_DELETE(ConfigImpl)

public:
    ConfigImpl() = default;
    virtual ~ConfigImpl() = default;

    // Ugly trick to work around the fact that virtual templates are not allowed
    /**
     * @brief Get the value of the config
     * @return A pointer to the value
     *
     * This function uses a type-erasure technique to work around the fact
     * that virtual templates are not allowed. We only know the true type of
     * the value if we know the template type, but this function cannot be a
     * template because it has to be overridden by the actual implementation.
     * Because of that, we return a void* to the value, assuming that the
     * Config class, which is a template and knows the type of the value, will
     * cast this pointer correctly and returns a properly typed value.
     *
     * \sa Config::value
     */
    virtual void *value(void) = 0;

    /**
     * @brief Lock the mutex of the config
     *
     * \sa unlock
     */
    virtual void lock(void) = 0;

    /**
     * @brief Unlock the mutex of the config
     *
     * \sa lock
     */
    virtual void unlock(void) = 0;

    /**
     * @brief Check if the config value changed
     * @return True if the config value changed, false otherwise
     */
    virtual bool changed(void) = 0;
};

#endif // CONFIG_IMPL_H
