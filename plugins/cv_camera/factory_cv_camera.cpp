
#include "factory_cv_camera.h"
#include "plugin/plugin_manager.h"
#include "cv_camera_item.h"

FactoryCvCamera::FactoryCvCamera()
{
}

bool FactoryCvCamera::init()
{
    PluginManager::instance()->addPluginComponent<CvCameraItem, AbstractItem>();
    return true;
}
