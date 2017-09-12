
#include "factory_frame_delayer.h"
#include "frame_delayer_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/plugin_manager.h"

FactoryFrameDelayer::FactoryFrameDelayer()
{
}

bool FactoryFrameDelayer::init()
{
    PluginManager::instance()->addPluginComponent<FrameDelayerItem, AbstractItem>();
    return true;
}
#else
extern "C" {
// This is not in the header to prevent a name-clash
ROVIZ_EXPORT const char *rovizItemName = "FrameDelayerItem";

RovizItemBase *rovizItemFactory(void)
{
    return new FrameDelayerItem();
}
}
#endif
