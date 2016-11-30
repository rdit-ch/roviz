
#include "factory_canny.h"
#include "plugin/plugin_manager.h"
#include "canny_item.h"

FactoryCanny::FactoryCanny()
{
}

bool FactoryCanny::init()
{
    PluginManager::instance()->addPluginComponent<CannyItem, AbstractItem>();
    return true;
}
