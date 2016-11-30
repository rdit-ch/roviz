
#include "factory_gray_conv.h"
#include "plugin/plugin_manager.h"
#include "gray_conv_item.h"

FactoryGrayConv::FactoryGrayConv()
{
}

bool FactoryGrayConv::init()
{
    PluginManager::instance()->addPluginComponent<GrayConvItem, AbstractItem>();
    return true;
}
