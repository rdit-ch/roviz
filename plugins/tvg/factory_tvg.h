#ifndef FACTORY_TVG_H
#define FACTORY_TVG_H

#include "plugin/interface_factory.h"
#include "core/abstract_robot_item.h"

class FactoryTVG : public InterfaceFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "FactoryTVG" FILE "tvg.json")
    Q_INTERFACES(InterfaceFactory)

public:
    FactoryTVG();

public:
    bool init();
};

#endif // FACTORY_TVG_H
