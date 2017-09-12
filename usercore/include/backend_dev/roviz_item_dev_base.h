#ifndef ROVIZITEMDEVBASE_H
#define ROVIZITEMDEVBASE_H

#include <string>
#include <functional>
#include <QScopedPointer>
#include <QMenu>
#include "item/abstract_item.h"
#include "core/export_handling.h"
#include "core/typedecl.h"
#include "core/trim.h"
#include "config/config_base.h"
#include "streams/stream_object.h"

// Needed by template_decl.cpp
// We include that here, because it is a non-portable dependency
#include "helper/startup_helper.h"

class QWidget;
class QGraphicsSceneMouseEvent;
class RovizItemDevBasePrivate;

/**
 * @brief Base class that binds RovizItem to the itemframework/Qt
 *
 * \sa RovizItem
 * \sa RovizItemDevBasePrivate
 */
class ROVIZ_EXPORT_CLASS RovizItemDevBase : public AbstractItem
{
    Q_OBJECT
    friend class RovizItemDevBasePrivate;

public:
    /**
     * @param type_name Name of the item
     */
    explicit RovizItemDevBase(std::string type_name);
    virtual ~RovizItemDevBase();

    /**
     * @return The main widget of the item
     *
     * Can be overwritten to show a custom widget (Enclose in #ifndef
     * ROVIZ_EXPORT when overriding). Before doing that, consider using a
     * custom stream and setting a new widget there.
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

protected:
    template<class T>
    Input addInputBase(std::string name);

    template<class T>
    Output addOutputBase(std::string name);

    virtual void pushOut(StreamObject obj, Output output);
    virtual Trim addTrimBase(Trim trim);
    virtual void addConfig(const ConfigBase &config);

public slots:
    virtual void start(void);
    virtual void stop(void);
    void restart(void);

protected slots:
    virtual void pushIn(StreamObject obj, Input input) = 0;
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
    QScopedPointer<RovizItemDevBasePrivate> _this;
};

#endif // ROVIZITEMDEVBASE_H
