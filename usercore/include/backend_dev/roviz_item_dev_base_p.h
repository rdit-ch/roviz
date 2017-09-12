#ifndef ROVIZITEMDEVBASEPRIVATE_H
#define ROVIZITEMDEVBASEPRIVATE_H

#include <QMap>
#include <QList>
#include <QImage>
#include "core/typedecl.h"

class QWidget;
class QPushButton;
class QSlider;
class QHBoxLayout;
class SettingsScope;
class StreamToInputMapper;
class RovizItemDevBase;
class ConfigImplDevBase;

/**
 * @brief Private part of RovizItemDevBase
 *
 * \sa RovizItemDevBase
 */
class RovizItemDevBasePrivate : public QObject
{
    Q_OBJECT

public:
    RovizItemDevBase *_this;
    QWidget *main_widget;
    QPushButton *collapse_btn;
    QHBoxLayout *main_layout, *main_image_layout, *main_control_layout;
    QMap<Output, QWidget*> out_widgets;
    QMap<ItemInput*, StreamToInputMapper*> in_mappers;
    QList<ConfigImplDevBase*> config_impls;
    QWidget *control_base;
    QImage default_image;
    QList<QMetaObject::Connection> trim_conns;
    bool config_present, conf_loaded;

    RovizItemDevBasePrivate(RovizItemDevBase *q);

public slots:
    /**
     * @brief The input was connected or disconnected
     */
    void inputStateChanged(void);

    /**
     * @brief (Un)collapses all trim sliders
     */
    void collapseBtnClicked(void);

    /**
     * @brief Adds the item to the shared window and loads the configs (cannot
     * be done in the constructor, because the SettingsScope is still
     * parentless)
     * @param Old SettingsScope
     */
    void parentScopeChanged(SettingsScope *old);

    /**
     * @brief Show the config window
     *
     * \sa Config
     */
    void showConfigWindow(void);
};

#endif // ROVIZITEMDEVBASEPRIVATE_H
