#ifndef FACTORY_SOBEL_H
#define FACTORY_SOBEL_H

#include "core/export_handling.h"
#include "core/roviz_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/interface_factory.h"

class FactorySobel : public InterfaceFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "FactorySobel" FILE "sobel.json")
    Q_INTERFACES(InterfaceFactory)

public:
    FactorySobel();

public:
    bool init();
};
#else
extern "C" {
roviz::ItemBase ROVIZ_EXPORT *rovizItemFactory(void);
}
#endif

#endif // FACTORY_SOBEL_H
