#ifndef FACTORY_SOBEL_H
#define FACTORY_SOBEL_H

#include "plugin/interface_factory.h"

class FactorySobel : public InterfaceFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "FactorySobel" FILE "sobel.json")
    Q_INTERFACES(InterfaceFactory)

public:
    FactorySobel();

public:
    bool init();
};

#endif // FACTORY_SOBEL_H
