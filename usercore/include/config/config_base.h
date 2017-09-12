#ifndef CONFIG_BASE_H
#define CONFIG_BASE_H

#include <QObject>

#include "core/export_handling.h"

/**
 * @brief Base class of Config that doesn't depend on the type
 *
 * \sa Config
 */
class ROVIZ_EXPORT_CLASS ConfigBase
{
public:
    virtual ~ConfigBase() = default;
    virtual ConfigImplBase *getImplBase(void) const = 0;
};

#endif // CONFIG_BASE_H
