
#include "project_config.h"

template<typename ConfigImplType>
void ProjectConfig::loadAll()
{
    this->configs["max_input_queue_size"] =
            (std::unique_ptr<ConfigImpl>(new ConfigImplType<int>(
            this->global_config.get(),
            "Max input queue size",
            16, 2, 512, false)));
}

template<typename ConfigImplType>
template<typename ValueType>
ConfigStorageType<ValueType>::type ProjectConfig::value(const std::string &config_name)
{
    auto iter = this->configs.find(config_name);
    if(iter == this->configs.end())
        return typename ConfigStorageType<ValueType>::type();

    // Same as in Config<T>
    ConfigImpl *config = iter->get();
    config->lock();
    typename ConfigStorageType<ValueType>::type val = *static_cast<typename ConfigStorageType<ValueType>::type*>(config->value());
    config->unlock();

    return val;
}

template<typename ConfigImplType>
const std::map<std::string, std::unique_ptr<ConfigImplType> > &ProjectConfig::getAll()
{
    return this->configs;
}
