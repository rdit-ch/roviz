#ifndef FACTORY_CONFIGMESSAGETEST_H
#define FACTORY_CONFIGMESSAGETEST_H

#include "core/export_handling.h"
#include "core/roviz_item.h"

#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
#include "plugin/interface_factory.h"

class FactoryConfigMessageTest : public InterfaceFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "FactoryConfigMessageTest" FILE "config_message_test.json")
    Q_INTERFACES(InterfaceFactory)

public:
    FactoryConfigMessageTest();

public:
    bool init();
};
#else
extern "C" {
roviz::ItemBase ROVIZ_EXPORT *rovizItemFactory(void);
}
#endif

#endif // FACTORY_CONFIGMESSAGETEST_H
