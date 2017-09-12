
#include "factory_gaussian_blur.h"
#include "gaussian_blur_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/plugin_manager.h"

FactoryGaussianBlur::FactoryGaussianBlur()
{
}

bool FactoryGaussianBlur::init()
{
    PluginManager::instance()->addPluginComponent<GaussianBlurItem, AbstractItem>();
    return true;
}
#else
extern "C" {
// This is not in the header to prevent a name-clash
ROVIZ_EXPORT const char *rovizItemName = "GaussianBlurItem";

RovizItemBase *rovizItemFactory(void)
{
    return new GaussianBlurItem();
}
}
#endif
