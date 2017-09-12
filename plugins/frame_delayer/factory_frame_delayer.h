#ifndef FACTORY_FRAMEDELAYER_H
#define FACTORY_FRAMEDELAYER_H

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

#endif // FACTORY_FRAMEDELAYER_H
