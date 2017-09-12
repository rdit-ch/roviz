#ifndef CONFIG_P_H
#define CONFIG_P_H

#include <string>
#include <mutex>
#include "core/export_handling.h"
#include ROVIZ_CONFIG_IMPL_INCLUDE

class RovizItem;

/**
 * @brief Private part of config
 */
template<typename T>
class ConfigPrivate
{
public:
    ConfigPrivate();

    RovizItem *parent;
    std::string name;
    ConfigImpl<T> impl;
    typename ConfigStorageType<T>::type val;
    std::mutex mtx;
    bool changed, restart_after_change;

    /**
     * @brief Initialize some generic values that all configs have in common
     * @param parent Item that the config belongs to, used to get the
     * settingsScope
     * @param name Name of the config
     * @param default_value Default value if no value is present in the config
     * file
     * @param restart_when_changed If true, the item will automatically be
     * restarted when changes to the config are applied
     */
    void init(RovizItem *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_value, bool restart_when_changed);
};

#endif // CONFIG_P_H
