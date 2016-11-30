
#include "factory_tvg.h"
#include "plugin/plugin_manager.h"
#include "tvg_item.h"

FactoryTVG::FactoryTVG()
{
}

bool FactoryTVG::init()
{
    PluginManager::instance()->addPluginComponent<TVGItem, AbstractItem>();
    return true;
}
