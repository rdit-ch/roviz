#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

#include <memory>
#include "config/config_storage_type.h"
#include "config/config_impl.h"

template<typename ConfigImplType>
class ProjectConfig
{
public:
    /**
     * @brief Loads all project specific configs
     *
     * This function will be called by the roviz framework and it should load
     * all configs that are project-based and don't depend on an individual
     * item.
     */
    virtual void loadAll(void);

    /**
     * @brief Get the value of a specific config
     * @param The name of the config
     * @return The value of the config
     *
     * The name of the config is the short name as used in the implementation of
     * load.
     */
    template<typename ValueType>
    typename ConfigStorageType<ValueType>::type value(const std::string &config_name);

    /**
     * @brief Get a map of all project-wide configs
     * @return All project-wide configs
     */
    const std::map<std::string, std::unique_ptr<ConfigImplType> > &getAll(void);

private:
    std::map<std::string, std::unique_ptr<ConfigImplType> > configs;
};

#endif // PROJECT_CONFIG_H
