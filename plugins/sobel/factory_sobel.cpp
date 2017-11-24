
#include "factory_sobel.h"
#include "sobel_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/plugin_manager.h"

FactorySobel::FactorySobel()
{
}

bool FactorySobel::init()
{
    PluginManager::instance()->addPluginComponent<SobelItem, AbstractItem>();
    return true;
}
#else
extern "C" {
// This is not in the header to prevent a name-clash
ROVIZ_EXPORT const char *rovizItemName = "SobelItem";

roviz::ItemBase *rovizItemFactory(void)
{
    return new SobelItem();
}
}
#endif
