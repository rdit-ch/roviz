#ifndef GLOBAL_CONFIG_H
#define GLOBAL_CONFIG_H

#include "backend_dev/config_parent.h"
#include "gui/config_dialog.h"

class GlobalConfig : public ConfigParent
{
public:
    explicit GlobalConfig(SettingsScope *scope);

    virtual SettingsScope *getSettingsScope(void) override;
    virtual void restart(void) override;

private:
    SettingsScope *settingsScope;
};

#endif // GLOBAL_CONFIG_H
