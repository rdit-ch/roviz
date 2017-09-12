#ifndef FACTORY_TIG_H
#define FACTORY_TIG_H

#include "core/export_handling.h"
#include "core/roviz_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/interface_factory.h"

class FactoryTIG : public InterfaceFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "FactoryTIG" FILE "tig.json")
    Q_INTERFACES(InterfaceFactory)

public:
    FactoryTIG();

public:
    bool init();
};
#else
extern "C" {
RovizItemBase ROVIZ_EXPORT *rovizItemFactory(void);
}
#endif

#endif // FACTORY_TIG_H
