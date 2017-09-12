#ifndef CONFIG_H
#define CONFIG_H

#include <memory>
#include <functional>
#include "core/export_handling.h"
#include ROVIZ_CONFIG_IMPL_INCLUDE
#include "config/config_p.h"
#include "config/config_base.h"
#include "config/config_storage_type.h"
#include "config/file_path.h"

class RovizItem;

/**
 * @brief Storage for the configuration of an item
 *
 * You can store configurations that you rarely change using this class. Always
 * use the RovizItem::addConfig functions to construct a Config!
 *
 * \sa ConfigBase
 * \sa Trim
 * \sa ConfigPrivate
 */
template<typename T>
class ROVIZ_EXPORT_CLASS Config : public ConfigBase
{
public:
    /**
     * @brief Constructs an empty config, do not use manually
     */
    Config();

    /**
     * @name Config interface
     *
     * Look at RovizItem::addConfig for an explanation of the parameters.
     * Never use those directly, always use RovizItem::addConfig!
     */
    ///@{
    Config(RovizItem *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_value, int min, int max, bool restart_when_changed = false);
    Config(RovizItem *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_value, double min, double max, bool restart_when_changed = false);
    Config(RovizItem *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_value, std::function<bool (std::string&)> checker = [](std::string s){return s;}, bool restart_when_changed = false);
    Config(RovizItem *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_index, const std::list<std::string> &possibilities, bool restart_when_changed = false);
    Config(RovizItem *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_value, bool restart_when_changed = false);
    Config(RovizItem *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_value, enum FilePath::Mode file_mode, const std::string &filter, bool restart_when_changed = false);
    ///@}
    ~Config() = default;

    // Don't allow copies
    Config(const Config &config) = delete;
    Config &operator=(const Config &config) = delete;

    // Allow moving
    Config(Config &&config);
    Config &operator=(Config &&config);

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

    // TODO Make private and friend?
    /**
     * @brief Get the implementation base
     * @return Pointer to the implementation
     */
    ConfigImplBase *getImplBase(void) const override;

private:
    std::unique_ptr<ConfigPrivate<T> > _this;
};

#endif // CONFIG_H
