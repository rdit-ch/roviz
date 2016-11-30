#ifndef FACTORY_TEMPLATE_UPPER_H
#define FACTORY_TEMPLATE_UPPER_H

#include "plugin/interface_factory.h"
#include "core/abstract_robot_item.h"

class FactoryTEMPLATE_CLASS : public InterfaceFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "FactoryTEMPLATE_CLASS" FILE "TEMPLATE_FILE.json")
    Q_INTERFACES(InterfaceFactory)

public:
    FactoryTEMPLATE_CLASS();

public:
    bool init();
};

#endif // FACTORY_TEMPLATE_UPPER_H
