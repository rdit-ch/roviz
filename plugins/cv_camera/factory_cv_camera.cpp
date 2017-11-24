
#include "factory_cv_camera.h"
#include "cv_camera_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/plugin_manager.h"

FactoryCvCamera::FactoryCvCamera()
{
}

bool FactoryCvCamera::init()
{
    PluginManager::instance()->addPluginComponent<CvCameraItem, AbstractItem>();
    return true;
}
#else
extern "C" {
// This is not in the header to prevent a name-clash
ROVIZ_EXPORT const char *rovizItemName = "CvCameraItem";

roviz::ItemBase *rovizItemFactory(void)
{
    return new CvCameraItem();
}
}
#endif
