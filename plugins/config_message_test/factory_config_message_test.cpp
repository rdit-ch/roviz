
#include "factory_config_message_test.h"
#include "config_message_test_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/plugin_manager.h"

FactoryConfigMessageTest::FactoryConfigMessageTest()
{
}

bool FactoryConfigMessageTest::init()
{
    PluginManager::instance()->addPluginComponent<ConfigMessageTestItem, AbstractItem>();
    return true;
}
#else
extern "C" {
// This is not in the header to prevent a name-clash
ROVIZ_EXPORT const char *rovizItemName = "ConfigMessageTestItem";

RovizItemBase *rovizItemFactory(void)
{
    return new ConfigMessageTestItem();
}
}
#endif

