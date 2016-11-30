#ifndef FACTORY_GRAYCONV_H
#define FACTORY_GRAYCONV_H

#include "plugin/interface_factory.h"

class FactoryGrayConv : public InterfaceFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "FactoryGrayConv" FILE "gray_conv.json")
    Q_INTERFACES(InterfaceFactory)

public:
    FactoryGrayConv();

public:
    bool init() override;
};

#endif // FACTORY_GRAYCONV_H
