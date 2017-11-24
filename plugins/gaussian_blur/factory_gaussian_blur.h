#ifndef FACTORY_GAUSSIANBLUR_H
#define FACTORY_GAUSSIANBLUR_H

#include "core/export_handling.h"
#include "core/roviz_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/interface_factory.h"

class FactoryGaussianBlur : public InterfaceFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "FactoryGaussianBlur" FILE "gaussian_blur.json")
    Q_INTERFACES(InterfaceFactory)

public:
    FactoryGaussianBlur();

public:
    bool init() override;
};
#else
extern "C" {
ROVIZ_EXPORT roviz::ItemBase ROVIZ_EXPORT *rovizItemFactory(void);
}
#endif

#endif // FACTORY_GAUSSIANBLUR_H
