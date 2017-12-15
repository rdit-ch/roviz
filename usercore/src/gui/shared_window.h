#ifndef SHARED_WINDOW_H
#define SHARED_WINDOW_H

#include <QMainWindow>
#include <QList>
#include <QVector>
#include <QMap>
#include <QByteArray>
#include <QIcon>
#include <memory>
#include "core/export_handling.h"
#include "backend_dev/global_config.h"
#include "backend_dev/config_impl_base_dev.h"

class RovizItemBaseDev;
class QCloseEvent;
class SettingsScope;
class QObject;
class QDockWidget;
class QToolButton;
class QTabBar;
class QLineEdit;
class QWidget;

/**
 * @brief Provides a shared window that displays data from all items
 *
 * There is one SharedWindow per project, each one displaying the images of all
 * items on the scene in one aggregated window. It also handles the
 * start/pause/stop mechanism.
 */
class SharedWindow : public QMainWindow
{
Q_OBJECT

// Singleton
Q_DISABLE_COPY(SharedWindow)

public:
    SharedWindow() = default;
    ~SharedWindow() = default;

    /**
     * @brief Add an item to the shared window
     * @param item The item to add
     *
     * All items are added to the shared window right from the beginning,
     * because the shared window also has to handle the start/pause/stop events
     * of the items that are not visible.
     */
    void addItem(RovizItemBaseDev *item);

    /**
     * @brief Remove an item from the shared window
     * @param item The item to remove
     */
    void removeItem(RovizItemBaseDev *item);

    /**
     * @brief Loads the config (if not already done) and shows the window
     */
    void load(void);

    /**
     * @brief Get the SharedWindow instance of a certain project
     * @param proj The current project
     * @return The SharedWindow instance
     *
     * Projects are identified through their SettingsScope.
     */
    static SharedWindow *instance(SettingsScope *proj);

protected:
    /**
     * @brief Called when the window is closed
     * @param event The close event
     *
     * See QWidget::closeEvent
     */
    void closeEvent(QCloseEvent *event) override;

private:
    static QMap<SettingsScope*, SharedWindow*> inst;

    const QIcon ico_start, ico_restart, ico_pause, ico_unpause, ico_stop, ico_new_tab, ico_settings;

    QList<QDockWidget*> dock_items;
    QList<RovizItemBaseDev*> parents;
    bool running, paused, initialized;
    SettingsScope *project_settings;
    QToolButton *btn_start, *btn_pause, *btn_stop, *btn_new_tab, *btn_settings;
    QTabBar *tab;
    QMainWindow *main_window;
    int active_tab;
    QVector<QByteArray> states;
    QLineEdit *rename_edit;
    int rename_index;
    std::unique_ptr<GlobalConfig> global_config;
    ConfigDialog config_dialog;
    std::list<std::unique_ptr<ConfigImplBaseDev> > configs;

    // Singleton
    SharedWindow(QWidget *parent);

    bool allChildrenClosed(void);

private slots:
    void destroy(void);
    void start(void);
    void pause(void);
    void stop(void);
    void showSettings(void);
    void addTab(void);
    void changeToTab(int index);
    void tabClosed(int index);
    void tabMoved(int to, int from);
    void tabStartRename(int index);
    void tabFinishRename(void);
    void itemClosed(void);
};

#endif // SHARED_WINDOW_H
