#ifndef CONFIG_PARENT_H
#define CONFIG_PARENT_H

#include "core/export_handling.h"

class SettingsScope;

class ConfigParent
{
public:
    virtual SettingsScope *getSettingsScope(void) = 0;
    virtual void restart(void) = 0;
};

#endif // CONFIG_PARENT_H
