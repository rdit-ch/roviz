
#include "factory_frame_delayer.h"
#include "plugin/plugin_manager.h"
#include "frame_delayer_item.h"

FactoryFrameDelayer::FactoryFrameDelayer()
{
}

bool FactoryFrameDelayer::init()
{
    PluginManager::instance()->addPluginComponent<FrameDelayerItem, AbstractItem>();
    return true;
}
