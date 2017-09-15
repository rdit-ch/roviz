#ifndef CONFIG_IMPL_BASE_DEV_H
#define CONFIG_IMPL_BASE_DEV_H

#include "config/config_impl.h"

class QWidget;

/**
 * @brief Base class of ConfigImplDev that doesn't depend on the type of the
 * config
 *
 * \sa Config
 * \sa ConfigImpl
 * \sa ConfigImplDev
 */
class ROVIZ_EXPORT ConfigImplBaseDev : public ConfigImpl
{
public:
    virtual ~ConfigImplBaseDev() = default;

    /**
     * @brief Get a widget representing this config type
     * @return A QWidget representing the config
     *
     * This is the widget that is shown when you open the config dialog
     */
    virtual QWidget *widget(void) const = 0;

    /**
     * @brief Load the value of this config from the settings scope
     *
     * Note: It can't be loaded in the constructor becuaes the settings
     * scope is not valid yet at that time.
     *
     * \sa ConfigImplDev::load
     */
    virtual void load(void) = 0;

    /**
     * @brief Notify the item that the config value changed
     *
     * This notifies the config that the user changed the config and that
     * those changes should be propagated to the plugin.
     *
     * \sa ConfigImplDev::refresh
     */
    virtual void refresh(void) = 0;
};

#endif // CONFIG_IMPL_BASE_DEV_H
