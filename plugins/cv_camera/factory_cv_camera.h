#ifndef FACTORY_CVCAMERA_H
#define FACTORY_CVCAMERA_H

#include "core/export_handling.h"
#include "core/roviz_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/interface_factory.h"

class FactoryCvCamera : public InterfaceFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "FactoryCvCamera" FILE "cv_camera.json")
    Q_INTERFACES(InterfaceFactory)

public:
    FactoryCvCamera();

public:
    bool init();
};
#else
extern "C" {
roviz::ItemBase ROVIZ_EXPORT *rovizItemFactory(void);
}
#endif

#endif // FACTORY_CVCAMERA_H
