#ifndef CONFIG_H
#define CONFIG_H

#include <memory>
#include "core/export_handling.h"
#include "config/config_storage_type.h"
#include "config/config_impl.h"

namespace roviz
{

/**
 * @brief Storage for the configuration of an item
 *
 * You can store configurations that you rarely change using this class. Always
 * use the Item::addConfig functions to construct a Config!
 *
 * \sa ConfigBase
 * \sa Trim
 * \sa ConfigPrivate
 */
template<typename T>
class ROVIZ_EXPORT Config
{
COPY_DELETE(Config<T>)
MOVE_DEFAULT(Config<T>)

public:
    /**
     * @brief Constructs an empty config, don't try to access it
     */
    Config() = default;
    ~Config() = default;

    /**
     * @name Config interface
     *
     * Look at Item::addConfig for an explanation of the parameters.
     * Never use those directly, always use Item::addConfig!
     */
    Config(ConfigImpl *impl);

    /**
     * @brief Get the current value stored in the config
     * @return The value with the appropriate type
     */
    typename ConfigStorageType<T>::type value(void);

    /**
     * @brief Check, wether the value stored in the config has changed since it
     * was last accessed.
     * @return true, if the value changed, false otherwise
     */
    bool changed(void);

private:
    std::unique_ptr<ConfigImpl> impl;
};

}

#endif // CONFIG_H
