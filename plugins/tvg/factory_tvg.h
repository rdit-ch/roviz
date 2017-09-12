#ifndef FACTORY_TVG_H
#define FACTORY_TVG_H

#include "core/export_handling.h"
#include "core/roviz_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/interface_factory.h"

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
#else
extern "C" {
RovizItemBase ROVIZ_EXPORT *rovizItemFactory(void);
}
#endif

#endif // FACTORY_TVG_H
