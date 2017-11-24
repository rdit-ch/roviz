#ifndef FACTORY_SUBTRACTOR_H
#define FACTORY_SUBTRACTOR_H

#include "core/export_handling.h"
#include "core/roviz_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
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
#else
extern "C" {
roviz::ItemBase ROVIZ_EXPORT *rovizItemFactory(void);
}
#endif

#endif // FACTORY_SUBTRACTOR_H
