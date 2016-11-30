
#include "factory_subtractor.h"
#include "plugin/plugin_manager.h"
#include "subtractor_item.h"

FactorySubtractor::FactorySubtractor()
{
}

bool FactorySubtractor::init()
{
    PluginManager::instance()->addPluginComponent<SubtractorItem, AbstractItem>();
    return true;
}
