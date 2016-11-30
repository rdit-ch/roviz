
#include "factory_TEMPLATE_FILE.h"
#include "plugin/plugin_manager.h"
#include "TEMPLATE_FILE_item.h"

FactoryTEMPLATE_CLASS::FactoryTEMPLATE_CLASS()
{
}

bool FactoryTEMPLATE_CLASS::init()
{
    PluginManager::instance()->addPluginComponent<TEMPLATE_CLASSItem, AbstractItem>();
    return true;
}
