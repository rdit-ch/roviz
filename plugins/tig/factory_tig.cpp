
#include "factory_tig.h"
#include "tig_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/plugin_manager.h"

FactoryTIG::FactoryTIG()
{
}

bool FactoryTIG::init()
{
    PluginManager::instance()->addPluginComponent<TIGItem, AbstractItem>();
    return true;
}
#else
extern "C" {
// This is not in the header to prevent a name-clash
ROVIZ_EXPORT const char *rovizItemName = "TIGItem";

RovizItemBase *rovizItemFactory(void)
{
    return new TIGItem();
}
}
#endif
