#ifndef CONFIG_IMPL_CMDLINE_H
#define CONFIG_IMPL_CMDLINE_H

#include <string>
#include "core/export_handling.h"
#include "config/config_storage_type.h"
#include "backend_cmdline/config_impl_base_cmdline.h"

/**
 * @brief The Config implementation for the Cmdline backend
 *
 * This implementation can only load a value from a string. Once it is loaded,
 * it doesn't change anymore.
 *
 * \sa Config
 * \sa ConfigImpl
 * \sa ConfigImplBaseCmdline
 */
template<class T>
class ConfigImplCmdline : public ConfigImplBaseCmdline
{
COPY_DELETE(ConfigImplCmdline)
MOVE_DELETE(ConfigImplCmdline)

public:
    ConfigImplCmdline() = default;
    ~ConfigImplCmdline() = default;

    /**
     * @brief Get the value of the config
     * @return A pointer to the value
     *
     * \sa ConfigImpl::value
     */
    void *value(void) override;

    /**
     * @brief Load the value from a string
     * @param value The string representation of the value
     *
     * This has to be done before the thread is run. Otherwise
     * a race condition might happen  because we don't lock anything.
     *
     * \sa ConfigImplBaseCmdline::load
     */
    void load(std::string value) override;

    /**
     * @brief Lock the mutex of the config
     *
     * As it will never happend that two threads access this config
     * at the same time, which is guaranteed by the design of the
     * Cmdline framework, this function doesn't do anything.
     *
     * \sa ConfigImpl::lock
     * \sa unlock
     */
    void lock(void) override;

    /**
     * @brief Unlock the mutex of the config
     *
     * As it will never happend that two threads access this config
     * at the same time, which is guaranteed by the design of the
     * Cmdline framework, this function doesn't do anything.
     *
     * \sa ConfigImpl::unlock
     * \sa lock
     */
    void unlock(void) override;

    /**
     * @brief Check if the config value changed
     * @return false
     *
     * Always returns false, because with that backend, the configs
     * cannot change.
     *
     * \sa ConfigImpl::changed
     */
    bool changed(void) override;

private:
    typename ConfigStorageType<T>::type val;
};

#endif // CONFIG_IMPL_CMDLINE_H
