
#include "factory_tvg.h"
#include "tvg_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/plugin_manager.h"

FactoryTVG::FactoryTVG()
{
}

bool FactoryTVG::init()
{
    PluginManager::instance()->addPluginComponent<TVGItem, AbstractItem>();
    return true;
}
#else
extern "C" {
// This is not in the header to prevent a name-clash
ROVIZ_EXPORT const char *rovizItemName = "TVGItem";

RovizItemBase *rovizItemFactory(void)
{
    return new TVGItem();
}
}
#endif
