#ifndef ABSTRACTROBOTITEMPRIVATE_H
#define ABSTRACTROBOTITEMPRIVATE_H

#include "core/abstract_robot_item.h"

class AbstractRobotItemPrivate : public QObject
{
    Q_OBJECT

public:
    AbstractRobotItem *_this;
    QWidget *main_widget;
    QPushButton *collapse_btn;
    QHBoxLayout *main_layout, *main_image_layout, *main_control_layout;
    QMap<void*, ImageWidget*> out_widgets;
    QMap<ItemInput*, StreamToImageInputMapper*> img_in_mappers;
    QMap<ItemInput*, StreamToMessageInputMapper*> msg_in_mappers;
    QList<QSlider*> sliders;
    QMap<QSlider*, SliderLabel*> slider_to_label;
    QWidget *control_base;
    QImage default_image;
    ConfigDialog *conf_diag;
    bool config_present, conf_loaded;

    AbstractRobotItemPrivate(AbstractRobotItem *q);

public slots:
    /**
     * @brief The image input was connected or disconnected
     */
    void imageInputStateChanged(void);

    /**
     * @brief The message input was connected or disconnected
     */
    void messageInputStateChanged(void);

    /**
     * @brief Wrapper that calls trimChanged()
     * @param value The new trim value
     */
    void trimChangedSlot(int value);

    /**
     * @brief (Un)collapses all trim sliders
     */
    void collapseBtnClicked(void);

    /**
     * @brief Saves all configs of the item
     */
    void saveConfigs(void);

    /**
     * @brief Restarts the item operation if the item is running
     */
    void restartIfRunning(void);

    /**
     * @brief Adds the item to the shared window (cannot be done in
     * the constructor, because the SettingsScope is still parentless.
     * @param Old SettingsScope
     */
    void parentScopeChanged(SettingsScope *old);
};

#endif // ABSTRACTROBOTITEMPRIVATE_H
