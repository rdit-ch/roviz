#ifndef ROVIZ_ITEM_BASE_DEV_PRIVATE_H
#define ROVIZ_ITEM_BASE_DEV_PRIVATE_H

#include <QMap>
#include <QList>
#include <QImage>

class QWidget;
class QPushButton;
class QHBoxLayout;
class SettingsScope;

namespace roviz
{

class ItemBaseDev;
class ConfigImplBaseDev;
class StreamWidget;

/**
 * @brief Private part of ItemDevBase
 *
 * \sa ItemDevBase
 */
class ItemBaseDevPrivate : public QObject
{
    Q_OBJECT

public:
    ItemBaseDev *_this;
    QWidget *main_widget;
    QPushButton *collapse_btn;
    QHBoxLayout *main_layout, *main_image_layout, *main_control_layout;
    QList<ConfigImplBaseDev*> config_impls;
    QWidget *control_base;
    QList<StreamWidget*> output_widgets;
    bool config_present, conf_loaded;

    ItemBaseDevPrivate(ItemBaseDev *q);

public slots:
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

    /**
     * @brief Does the generic initialization of a config implementation that
     * is not dependant on the type.
     * @param impl The implementation
     */
    void initConfigImpl(ConfigImplBaseDev *impl);
};

}

#endif // ROVIZ_ITEM_BASE_DEV_PRIVATE_H
