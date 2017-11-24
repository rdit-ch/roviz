#ifndef FACTORY_TEMPLATE_UPPER_H
#define FACTORY_TEMPLATE_UPPER_H

#include "core/export_handling.h"
#include "core/roviz_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/interface_factory.h"

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
#else
extern "C" {
roviz::ItemBase ROVIZ_EXPORT *rovizItemFactory(void);
}
#endif

#endif // FACTORY_TEMPLATE_UPPER_H
