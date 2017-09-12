
#include "config/config_p.h"

#include "core/template_decl.h"

template<typename T>
ConfigPrivate<T>::ConfigPrivate()
    : impl(this)
{
}

template<typename T>
void ConfigPrivate<T>::init(RovizItem *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_value, bool restart_when_changed)
{
    // We won't load the config values here, because settingsScope() is not
    // valid yet.
    this->parent = parent;
    this->name = name;
    this->val = default_value;
    this->changed = false;
    this->restart_after_change = restart_when_changed;
}

INSTANTIATE_CONFIG_PRIVATE
