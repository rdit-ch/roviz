#ifndef CONFIG_IMPL_DEV_H
#define CONFIG_IMPL_DEV_H

#include <mutex>
#include <functional>
#include <string>
#include <vector>
#include "core/export_handling.h"
#include "config/config_impl.h"
#include "config/config_storage_type.h"
#include "config/file_path.h"
#include "backend_dev/config_impl_base_dev.h"

class QWidget;

namespace roviz
{

class ItemBaseDev;

/**
 * @brief Dev implementation of the config interface
 *
 * Implements the saving of configs using the itemframeworks settings scope.
 *
 * \sa Config
 * \sa ConfigImpl
 * \sa ConfigImplDevBase
 */
template<typename T>
class ConfigImplDev : public ConfigImplBaseDev
{
COPY_DELETE(ConfigImplDev)
MOVE_DELETE(ConfigImplDev)

public:
    /**
     * @name Config interface implementation
     *
     * These are the same parameters that are used in Item.
     *
     * \sa Item
     */
    ///@{
    // Int
    ConfigImplDev(ItemBaseDev *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_value, int min, int max, bool restart_when_changed);

    // Double
    ConfigImplDev(ItemBaseDev *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_value, double min, double max, bool restart_when_changed);

    // String
    ConfigImplDev(ItemBaseDev *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_value, std::function<bool (std::string&)> checker, bool restart_when_changed);

    // List
    ConfigImplDev(ItemBaseDev *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_value, const std::vector<std::string> &possibilities, bool restart_when_changed);

    // Bool
    ConfigImplDev(ItemBaseDev *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_value, bool restart_when_changed);

    // Path
    ConfigImplDev(ItemBaseDev *parent, const std::string &name, const typename ConfigStorageType<T>::type &default_value, enum FilePath::Mode file_mode, const std::string &filter, bool restart_when_changed);
    ///}

    /**
     * @return The QWidget associated with this config
     *
     * Every config has a widget that is used to adjust the value. This function
     * returns the widget for this config.
     */
    QWidget *widget(void) const override;

    /**
     * @brief Load the value of this config from the settings scope
     *
     * Note: It can't be loaded in the constructor becuaes the settings
     * scope is not valid yet at that time.
     *
     * \sa ConfigImplBaseDev::load
     */
    void load(void);

    /**
     * @brief Called, when the config changes are applied
     */
    bool changed(void) override;

    /**
     * @brief Notify the item that the config value changed
     *
     * This notifies the config that the user changed the config and that
     * those changes should be propagated to the plugin.
     *
     * \sa ConfigImplBaseDev::refresh
     */
    void refresh(void) override;

    /**
     * @brief Lock the mutex of the config
     *
     * \sa ConfigImpl::lock
     * \sa unlock
     */
    void lock(void) override;

    /**
     * @brief Unlock the mutex of the config
     *
     * \sa ConfigImpl::unlock
     * \sa lock
     */
    void unlock(void) override;

    /**
     * @brief Get the value of the config
     * @return A pointer to the value
     *
     * \sa ConfigImpl::value
     */
    void *value(void) override;

private:
    ItemBaseDev *parent;
    std::string name;
    typename ConfigStorageType<T>::type val, tmp_val;
    QWidget *main_widget, *data_widget;
    std::mutex mtx;
    bool restart_after_change, has_changed, tmp_changed;

    void initMainWidget(QWidget *sub_widget);
    void save(void);
};

}

#endif // CONFIG_IMPL_DEV_H
