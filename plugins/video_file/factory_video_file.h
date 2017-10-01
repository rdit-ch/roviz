#ifndef FACTORY_VIDEOFILE_H
#define FACTORY_VIDEOFILE_H

#include "core/export_handling.h"
#include "core/roviz_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/interface_factory.h"

class FactoryVideoFile : public InterfaceFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "FactoryVideoFile" FILE "video_file.json")
    Q_INTERFACES(InterfaceFactory)

public:
    FactoryVideoFile();

public:
    bool init();
};
#else
extern "C" {
RovizItemBase ROVIZ_EXPORT *rovizItemFactory(void);
}
#endif

#endif // FACTORY_VIDEOFILE_H
