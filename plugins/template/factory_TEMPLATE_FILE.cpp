
#include "factory_TEMPLATE_FILE.h"
#include "TEMPLATE_FILE_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/plugin_manager.h"

FactoryTEMPLATE_CLASS::FactoryTEMPLATE_CLASS()
{
}

bool FactoryTEMPLATE_CLASS::init()
{
    PluginManager::instance()->addPluginComponent<TEMPLATE_CLASSItem, AbstractItem>();
    return true;
}
#else
extern "C" {
// This is not in the header to prevent a name-clash
ROVIZ_EXPORT const char *rovizItemName = "TEMPLATE_CLASSItem";

roviz::ItemBase *rovizItemFactory(void)
{
    return new TEMPLATE_CLASSItem();
}
}
#endif

