#ifndef FACTORY_CANNY_H
#define FACTORY_CANNY_H

#include "plugin/interface_factory.h"
#include "core/abstract_robot_item.h"

class FactoryCanny : public InterfaceFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "FactoryCanny" FILE "canny.json")
    Q_INTERFACES(InterfaceFactory)

public:
    FactoryCanny();

public:
    bool init();
};

#endif // FACTORY_CANNY_H
