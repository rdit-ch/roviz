
#include "factory_subtractor.h"
#include "subtractor_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/plugin_manager.h"

FactorySubtractor::FactorySubtractor()
{
}

bool FactorySubtractor::init()
{
    PluginManager::instance()->addPluginComponent<SubtractorItem, AbstractItem>();
    return true;
}
#else
extern "C" {
// This is not in the header to prevent a name-clash
ROVIZ_EXPORT const char *rovizItemName = "SubtractorItem";

RovizItemBase *rovizItemFactory(void)
{
    return new SubtractorItem();
}
}
#endif
