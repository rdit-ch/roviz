
#include "factory_sobel.h"
#include "plugin/plugin_manager.h"
#include "sobel_item.h"

FactorySobel::FactorySobel()
{
}

bool FactorySobel::init()
{
    PluginManager::instance()->addPluginComponent<SobelItem, AbstractItem>();
    return true;
}
