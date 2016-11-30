#ifndef FACTORY_GAUSSIANBLUR_H
#define FACTORY_GAUSSIANBLUR_H

#include "plugin/interface_factory.h"
#include "core/abstract_robot_item.h"

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

#endif // FACTORY_GAUSSIANBLUR_H
