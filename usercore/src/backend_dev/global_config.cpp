
#include "global_config.h"

GlobalConfig::GlobalConfig(SettingsScope *scope)
    : settingsScope(scope)
{
}

SettingsScope *GlobalConfig::getSettingsScope()
{
    return this->settingsScope;
}

void GlobalConfig::restart()
{
}
