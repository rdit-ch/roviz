#ifndef ROVIZ_ITEM_BASE_CMDLINE_H
#define ROVIZ_ITEM_BASE_CMDLINE_H

#include <memory>
#include <functional>
#include <string>
#include <list>
#include "core/export_handling.h"
#include "backend_cmdline/roviz_item_base_cmdline_p.h"
#include "config/config_storage_type.h"
#include "core/input.h"
#include "core/output.h"

class TrimImpl;
class ConfigImpl;

/**
 * @brief The RovizItem implementation for the Cmdline backend
 *
 * \sa RovizItem
 */
class ROVIZ_EXPORT RovizItemBaseCmdline
{
public:
    /**
     * @brief Constructor
     * @param name Ignored for this backend
     */
    explicit RovizItemBaseCmdline(std::string name);
    virtual ~RovizItemBaseCmdline() = default;

    /**
     * @brief Connect an input of this item to an output of another item
     * @param input_index The input index of the input to connect
     * @param from_item The other item that contains the output
     * @param output_index The output index of the output to connect
     * @return true, if the connect was successful, false otherwise
     *
     * \sa Input::connect
     * \sa Output::connect
     */
    bool connect(int input_index, RovizItemBaseCmdline *from_item, int output_index);

    /**
     * @brief Set the value of a Trim
     * @param name The name of the Trim
     * @param value The value
     */
    void setTrim(std::string name, double value);

    /**
     * @name Interface implementation
     *
     * Implementation of the interface that RovizItem demands.
     * See the documentation of RovizItem to see what these functions
     * do.
     *
     * \sa RovizItem
     */
    ///@{
    virtual void pause(void) = 0;
    virtual void unpause(void) = 0;
    virtual bool running(void) const = 0;
    virtual void join(void) = 0;

protected:
    template<class T>
    Input<T> addInputBase(std::string name, RovizItem *item);

    template<class T>
    Output<T> addOutputBase(std::string name);

    TrimImpl *getTrimImpl(std::string name, double default_value, double min, double max, int steps, bool logarithmic, std::function<void (double)> notifier_func);

    ConfigImpl *getConfigImpl(const std::string &name, const typename ConfigStorageType<int>::type &default_value, int min, int max, bool restart_when_changed);
    ConfigImpl *getConfigImpl(const std::string &name, const typename ConfigStorageType<double>::type &default_value, double min, double max, bool restart_when_changed);
    ConfigImpl *getConfigImpl(const std::string &name, const typename ConfigStorageType<std::string>::type &default_value, std::function<bool (std::string&)> checker, bool restart_when_changed);
    ConfigImpl *getConfigImpl(const std::string &name, const typename ConfigStorageType<std::vector<std::string> >::type &default_index, const std::vector<std::string> &possibilities, bool restart_when_changed);
    ConfigImpl *getConfigImpl(const std::string &name, const typename ConfigStorageType<bool>::type &default_value, bool restart_when_changed);
    ConfigImpl *getConfigImpl(const std::string &name, const typename ConfigStorageType<FilePath>::type &default_value, enum FilePath::Mode file_mode, const std::string &filter, bool restart_when_changed);

public:
    virtual void start(void);
    virtual void stop(void);
    ///@}

    // This is public to allow the starter (ProjectParser) access
    std::unique_ptr<RovizItemBaseCmdlinePrivate> _this_base;
};

#endif // ROVIZ_ITEM_BASE_CMDLINE_H
