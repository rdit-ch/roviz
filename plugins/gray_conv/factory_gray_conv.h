#ifndef FACTORY_GRAYCONV_H
#define FACTORY_GRAYCONV_H

#include "core/export_handling.h"
#include "core/roviz_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
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
#else
extern "C" {
RovizItemBase ROVIZ_EXPORT *rovizItemFactory(void);
}
#endif

#endif // FACTORY_GRAYCONV_H
