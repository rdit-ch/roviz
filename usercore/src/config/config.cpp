
#include "config/config.h"
#include "core/template_decl.h"
#include "core/logger.h"

namespace roviz
{

template<typename T>
Config<T>::Config(ConfigImpl *impl)
    : impl(impl)
{
    logger->error_if(impl == nullptr, "Trying to construct a config without an implementation");
}

template<typename T>
typename ConfigStorageType<T>::type Config<T>::value()
{
    if(this->impl == nullptr)
    {
        logger->warn("Trying to acces the value of a config without an implementation ({})", typeid(T).name());
        return typename ConfigStorageType<T>::type();
    }

    // Yes, that's a really ugly typecast, but if you don't fuck
    // up really hard, it should be impossible to fail.
    // Also, we lock to prevent an extremely unlikely race-condition.
    this->impl->lock();
    typename ConfigStorageType<T>::type val = *static_cast<typename ConfigStorageType<T>::type*>(this->impl->value());
    this->impl->unlock();

    return val;
}

template<typename T>
bool Config<T>::changed()
{
    if(this->impl == nullptr)
    {
        logger->warn("Trying to check wether a config without an implementation changed ({})", typeid(T).name());
        return false;
    }

    return this->impl->changed();
}

#define INSTANTIATE_CONFIG(T) template class Config<T>;

DO_FOR_ALL_CONFIG_TYPES(INSTANTIATE_CONFIG)

}
