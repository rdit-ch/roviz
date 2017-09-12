#ifndef CONFIG_IMPL_DEV_H
#define CONFIG_IMPL_DEV_H

#include <functional>
#include <QObject>
#include "backend_dev/config_impl_dev_base.h"
#include "config/config_storage_type.h"
#include "config/file_path.h"
#include "core/export_handling.h"

class QWidget;
class QHBoxLayout;
class QLabel;

template<typename T>
class ConfigPrivate;

/**
 * @brief Dev implementation of the config interface
 *
 * Implements the saving of configs using itemframeworks settingsScope().
 *
 * \sa Config
 * \sa ConfigPrivate
 * \sa ConfigImplDevBase
 */
template<typename T>
class ROVIZ_EXPORT_CLASS ConfigImplDev : public ConfigImplDevBase
{
public:
    /**
     * @param config Private data of the config
     */
    ConfigImplDev(ConfigPrivate<T> *config);

    /**
     * @return The QWidget associated with this config
     *
     * Every config has a widget that is used to adjust the value. This function
     * returns the widget for this config.
     */
    QWidget *widget() const override;

    /**
     * @brief Load the config from the settingsScope().
     */
    void load(void);

    /**
     * @return true, if the item should be restarted when a config changes,
     * false otherwise.
     */
    bool restartAfterChange(void) const override;

    /**
     * @brief Initialize the config (int)
     *
     * \sa Config
     */
    void init(int min, int max);

    /**
     * @brief Initialize the config (double)
     *
     * \sa Config
     */
    void init(double min, double max);

    /**
     * @brief Initialize the config (string)
     *
     * \sa Config
     */
    void init(std::function<bool (std::string&)> checker);

    /**
     * @brief Initialize the config (list)
     *
     * \sa Config
     */
    void init(const std::list<std::string> &possibilities); // TODO check 'API' version (possibilities)

    /**
     * @brief Initialize the config (bool)
     *
     * \sa Config
     */
    void init(void);

    /**
     * @brief Initialize the config (file path)
     *
     * \sa Config
     */
    void init(const std::string &filter, enum FilePath::Mode file_mode);

    /**
     * @brief Called, when the config changes are applied
     */
    void changed(void) override;

private:
    ConfigPrivate<T> *_this;
    QWidget *main_widget, *data_widget;
    typename ConfigStorageType<T>::type tmp_val;
    bool tmp_changed;

    void initMainWidget(QWidget *sub_widget);
    void save(void);
};

#endif // CONFIG_IMPL_DEV_H
