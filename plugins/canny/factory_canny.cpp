
#include "factory_canny.h"
#include "canny_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/plugin_manager.h"

FactoryCanny::FactoryCanny()
{
}

bool FactoryCanny::init()
{
    PluginManager::instance()->addPluginComponent<CannyItem, AbstractItem>();
    return true;
}
#else
extern "C" {
// This is not in the header to prevent a name-clash
ROVIZ_EXPORT const char *rovizItemName = "CannyItem";

RovizItemBase *rovizItemFactory(void)
{
    return new CannyItem();
}
}
#endif
