#ifndef FACTORY_TIG_H
#define FACTORY_TIG_H

#include "plugin/interface_factory.h"

class FactoryTIG : public InterfaceFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "FactoryTIG" FILE "tig.json")
    Q_INTERFACES(InterfaceFactory)

public:
    FactoryTIG();

public:
    bool init();
};

#endif // FACTORY_TIG_H
