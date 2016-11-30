
#include "factory_gaussian_blur.h"
#include "plugin/plugin_manager.h"
#include "gaussian_blur_item.h"

FactoryGaussianBlur::FactoryGaussianBlur()
{
}

bool FactoryGaussianBlur::init()
{
    PluginManager::instance()->addPluginComponent<GaussianBlurItem, AbstractItem>();
    return true;
}
