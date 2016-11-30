
#include "factory_tig.h"
#include "plugin/plugin_manager.h"
#include "tig_item.h"

FactoryTIG::FactoryTIG()
{
}

bool FactoryTIG::init()
{
    PluginManager::instance()->addPluginComponent<TIGItem, AbstractItem>();
    return true;
}
