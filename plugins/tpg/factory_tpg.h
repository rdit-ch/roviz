#ifndef FACTORY_TPG_H
#define FACTORY_TPG_H

#include "core/export_handling.h"
#include "core/roviz_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
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
#endif

#endif // FACTORY_TPG_H
