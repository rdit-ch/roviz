#ifndef ROVIZ_ITEM_BASE_DEV_H
#define ROVIZ_ITEM_BASE_DEV_H

#include <string>
#include <functional>
#include <QScopedPointer>
#include <QMenu>
#include "item/abstract_item.h"
#include "core/export_handling.h"
#include "backend_dev/roviz_item_base_dev_p.h"
#include "core/input.h"
#include "core/output.h"
#include "config/config_storage_type.h"

class QGraphicsSceneMouseEvent;
class ConfigImpl;
class TrimImpl;

/**
 * @brief Base class that binds RovizItem to the itemframework/Qt
 *
 * \sa RovizItem
 * \sa RovizItemDevBasePrivate
 */
class ROVIZ_EXPORT RovizItemBaseDev : public AbstractItem
{
    Q_OBJECT
    friend class RovizItemBaseDevPrivate;

public:
    /**
     * @param type_name Name of the item
     */
    explicit RovizItemBaseDev(std::string type_name);
    virtual ~RovizItemBaseDev();

    /**
     * @return The main widget of the item
     *
     * Can be overwritten to show a custom widget. Before doing that,
     * consider using a custom stream and setting a new widget there.
     *
     * \sa SharedWindow
     */
    virtual QWidget *widget(void);

    /**
     * @name Interface implementation
     *
     * Implementation of the interface that RovizItem demands.
     * See the documentation of RovizItem to see what these functions
     * do.
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

    // Note: The signatures of the getConfigImpl() functions is distinct for every type,
    // so we don't really need a template here. We also wouldn't need one in RovizItem
    // in the first place, but in the future, there might come more configs with the same
    // signature and introducing templates at that point would mean rewriting all plugins.
    // If a config with the same signature comes up in the futere, we can safely switch to
    // a template here without breaking the plugins.

    ConfigImpl *getConfigImpl(const std::string &name, const typename ConfigStorageType<int>::type &default_value, int min, int max, bool restart_when_changed);
    ConfigImpl *getConfigImpl(const std::string &name, const typename ConfigStorageType<double>::type &default_value, double min, double max, bool restart_when_changed);
    ConfigImpl *getConfigImpl(const std::string &name, const typename ConfigStorageType<std::string>::type &default_value, std::function<bool (std::string&)> checker, bool restart_when_changed);
    ConfigImpl *getConfigImpl(const std::string &name, const typename ConfigStorageType<std::vector<std::string> >::type &default_index, const std::vector<std::string> &possibilities, bool restart_when_changed);
    ConfigImpl *getConfigImpl(const std::string &name, const typename ConfigStorageType<bool>::type &default_value, bool restart_when_changed);
    ConfigImpl *getConfigImpl(const std::string &name, const typename ConfigStorageType<FilePath>::type &default_value, enum FilePath::Mode file_mode, const std::string &filter, bool restart_when_changed);

public slots:
    virtual void start(void);
    virtual void stop(void);
    void restart(void);
    ///@}

protected:
    /**
     * @brief Opens the item in the SharedWindow
     */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

    /**
     * @brief Show the 'Configure' option in the context menu if the item has
     * configs
     * @param menu The context menu
     */
    void contextMenuPrepare(QMenu &menu) const override;

private:
    QScopedPointer<RovizItemBaseDevPrivate> _this;
};

#endif // ROVIZ_ITEM_BASE_DEV_H
