#ifndef FACTORY_SUBTRACTOR_H
#define FACTORY_SUBTRACTOR_H

#include "plugin/interface_factory.h"

class FactorySubtractor : public InterfaceFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "FactorySubtractor" FILE "subtractor.json")
    Q_INTERFACES(InterfaceFactory)

public:
    FactorySubtractor();

public:
    bool init() override;
};

#endif // FACTORY_SUBTRACTOR_H
