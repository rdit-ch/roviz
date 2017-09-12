#ifndef CONFIG_IMPL_DEV_BASE_H
#define CONFIG_IMPL_DEV_BASE_H

#include <QObject>

class QWidget;

/**
 * @brief Base class of ConfigImplDev that doesn't depend on the type of the
 * config
 *
 * \sa Config
 */
class ConfigImplDevBase
{
public:
    virtual ~ConfigImplDevBase() = default;
    virtual QWidget *widget(void) const = 0;
    virtual bool restartAfterChange(void) const = 0;
    virtual void changed(void) = 0;
    virtual void load(void) = 0;
};

#endif // CONFIG_IMPL_DEV_BASE_H
