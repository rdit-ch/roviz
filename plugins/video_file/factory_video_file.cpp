
#include "factory_video_file.h"
#include "video_file_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/plugin_manager.h"

FactoryVideoFile::FactoryVideoFile()
{
}

bool FactoryVideoFile::init()
{
    PluginManager::instance()->addPluginComponent<VideoFileItem, AbstractItem>();
    return true;
}
#else
extern "C" {
// This is not in the header to prevent a name-clash
ROVIZ_EXPORT const char *rovizItemName = "VideoFileItem";

roviz::ItemBase *rovizItemFactory(void)
{
    return new VideoFileItem();
}
}
#endif

