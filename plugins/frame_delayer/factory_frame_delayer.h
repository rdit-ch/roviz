#ifndef FACTORY_FRAMEDELAYER_H
#define FACTORY_FRAMEDELAYER_H

#include "core/export_handling.h"
#include "core/roviz_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/interface_factory.h"

class FactoryFrameDelayer : public InterfaceFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "FactoryFrameDelayer" FILE "frame_delayer.json")
    Q_INTERFACES(InterfaceFactory)

public:
    FactoryFrameDelayer();

public:
    bool init() override;
};
#else
extern "C" {
roviz::ItemBase ROVIZ_EXPORT *rovizItemFactory(void);
}
#endif

#endif // FACTORY_FRAMEDELAYER_H
