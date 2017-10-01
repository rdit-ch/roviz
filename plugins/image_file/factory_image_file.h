#ifndef FACTORY_IMAGEFILE_H
#define FACTORY_IMAGEFILE_H

#include "core/export_handling.h"
#include "core/roviz_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/interface_factory.h"

class FactoryImageFile : public InterfaceFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "FactoryImageFile" FILE "image_file.json")
    Q_INTERFACES(InterfaceFactory)

public:
    FactoryImageFile();

public:
    bool init();
};
#else
extern "C" {
RovizItemBase ROVIZ_EXPORT *rovizItemFactory(void);
}
#endif

#endif // FACTORY_IMAGEFILE_H
