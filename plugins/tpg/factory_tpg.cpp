
#include "factory_tpg.h"
#include "plugin/plugin_manager.h"
#include "tpg_item.h"

FactoryTPG::FactoryTPG()
{
}

bool FactoryTPG::init()
{
    PluginManager::instance()->addPluginComponent<TPGItem, AbstractItem>();
    return true;
}
