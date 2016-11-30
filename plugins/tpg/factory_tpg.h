#ifndef FACTORY_TPG_H
#define FACTORY_TPG_H

#include "plugin/interface_factory.h"

class FactoryTPG : public InterfaceFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "FactoryTPG" FILE "tpg.json")
    Q_INTERFACES(InterfaceFactory)

public:
    FactoryTPG();

public:
    bool init() override;
};

#endif // FACTORY_TPG_H
