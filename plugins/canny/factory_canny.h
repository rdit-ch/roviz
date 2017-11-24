#ifndef FACTORY_CANNY_H
#define FACTORY_CANNY_H

#include "core/export_handling.h"
#include "core/roviz_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/interface_factory.h"

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
#else
extern "C" {
roviz::ItemBase ROVIZ_EXPORT *rovizItemFactory(void);
}
#endif

#endif // FACTORY_CANNY_H
