
#include "factory_tpg.h"
#include "tpg_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/plugin_manager.h"

FactoryTPG::FactoryTPG()
{
}

bool FactoryTPG::init()
{
    PluginManager::instance()->addPluginComponent<TPGItem, AbstractItem>();
    return true;
}
#endif
