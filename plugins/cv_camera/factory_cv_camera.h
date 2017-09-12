#ifndef FACTORY_CVCAMERA_H
#define FACTORY_CVCAMERA_H

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

#endif // FACTORY_CVCAMERA_H
