#ifndef FACTORY_HARRISCORNER_H
#define FACTORY_HARRISCORNER_H

#include "core/export_handling.h"
#include "core/roviz_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/interface_factory.h"

class FactoryHarrisCorner : public InterfaceFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "FactoryHarrisCorner" FILE "harris_corner.json")
    Q_INTERFACES(InterfaceFactory)

public:
    FactoryHarrisCorner();

public:
    bool init();
};
#else
extern "C" {
roviz::ItemBase ROVIZ_EXPORT *rovizItemFactory(void);
}
#endif

#endif // FACTORY_HARRISCORNER_H
