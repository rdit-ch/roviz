
#include "factory_gray_conv.h"
#include "gray_conv_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/plugin_manager.h"

FactoryGrayConv::FactoryGrayConv()
{
}

bool FactoryGrayConv::init()
{
    PluginManager::instance()->addPluginComponent<GrayConvItem, AbstractItem>();
    return true;
}
#else
extern "C" {
// This is not in the header to prevent a name-clash
ROVIZ_EXPORT const char *rovizItemName = "GrayConvItem";

roviz::ItemBase *rovizItemFactory(void)
{
    return new GrayConvItem();
}
}
#endif
