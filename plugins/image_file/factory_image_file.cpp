
#include "factory_image_file.h"
#include "image_file_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/plugin_manager.h"

FactoryImageFile::FactoryImageFile()
{
}

bool FactoryImageFile::init()
{
    PluginManager::instance()->addPluginComponent<ImageFileItem, AbstractItem>();
    return true;
}
#else
extern "C" {
// This is not in the header to prevent a name-clash
ROVIZ_EXPORT const char *rovizItemName = "ImageFileItem";

RovizItemBase *rovizItemFactory(void)
{
    return new ImageFileItem();
}
}
#endif

