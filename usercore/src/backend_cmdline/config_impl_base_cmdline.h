#ifndef CONFIG_IMPL_BASE_CMDLINE_H
#define CONFIG_IMPL_BASE_CMDLINE_H

#include "core/export_handling.h"
#include "config/config_impl.h"

/**
 * @brief Base class for ConfigImplCmdline
 *
 * Does not need a template, but still allows loading a value.
 *
 * \sa Config
 * \sa ConfigImpl
 * \sa ConfigImplCmdline
 */
class ROVIZ_EXPORT ConfigImplBaseCmdline : public ConfigImpl
{
public:
    virtual ~ConfigImplBaseCmdline() = default;

    /**
     * @brief Load the value from a string
     * @param value The string representation of the value
     *
     * ConfigImplCmdline will determine how to parse the string based on its
     * template type.
     */
    virtual void load(std::string value) = 0;
};

#endif // CONFIG_IMPL_BASE_CMDLINE_H
