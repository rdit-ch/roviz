
#include "factory_harris_corner.h"
#include "harris_corner_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/plugin_manager.h"

FactoryHarrisCorner::FactoryHarrisCorner()
{
}

bool FactoryHarrisCorner::init()
{
    PluginManager::instance()->addPluginComponent<HarrisCornerItem, AbstractItem>();
    return true;
}
#else
extern "C" {
// This is not in the header to prevent a name-clash
ROVIZ_EXPORT const char *rovizItemName = "HarrisCornerItem";

RovizItemBase *rovizItemFactory(void)
{
    return new HarrisCornerItem();
}
}
#endif
