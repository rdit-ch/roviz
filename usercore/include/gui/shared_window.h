#ifndef SHARED_WINDOW_H
#define SHARED_WINDOW_H

#include <QObject>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMainWindow>
#include <QList>
#include <QMap>
#include <QDockWidget>
#include <QToolButton>
#include <QTabBar>
#include <QStringList>
#include <QVector>
#include <QVariant>
#include <QLineEdit>
#include "core/robot_core.h"
#include "core/abstract_robot_item.h"
#include "helper/settings_scope.h"
#include "gui/gui_manager.h"
#include "gui/dock_widget_signaling.h"

class AbstractRobotItem;

/**
 * @brief Provides a shared window that displays data from all items
 *
 * There is one SharedWindow per project, each one displaying the images of all
 * items on the scene in one aggregated window. It also handles the
 * start/pause/stop mechanism.
 *
 * \ingroup robot_framework
 */
class ROBOTCORE_EXPORT SharedWindow : public QMainWindow
{
Q_OBJECT

// Singleton
Q_DISABLE_COPY(SharedWindow)

public:
    ~SharedWindow();

    /**
     * @brief Add an item to the shared window
     * @param item The item to add
     *
     * All items are added to the shared window right from the beginning,
     * because the shared window also has to handle the start/pause/stop events
     * of the items that are not visible.
     */
    void addItem(AbstractRobotItem *item);

    /**
     * @brief Remove an item from the shared window
     * @param item The item to remove
     */
    void removeItem(AbstractRobotItem *item);

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

    void closeEvent(QCloseEvent *event) override;

private:
    static QMap<SettingsScope*, SharedWindow*> inst;

    const QIcon ico_start, ico_restart, ico_pause, ico_unpause, ico_stop, ico_new_tab;

    QObject *destructor;
    QList<QDockWidget*> dock_items;
    QList<AbstractRobotItem*> parents;
    bool running, paused, initialized;
    SettingsScope *project_settings;
    QToolButton *btn_start, *btn_pause, *btn_stop, *btn_new_tab;
    QTabBar *tab;
    QMainWindow *main_window;
    int active_tab;
    QVector<QByteArray> states;
    QLineEdit *rename_edit;
    int rename_index;

    // Singleton
    SharedWindow(QWidget *parent);

    bool allChildrenClosed(void);

public slots:
    void destroy(void);
    void start(void);
    void pause(void);
    void stop(void);
    void addTab(void);
    void changeToTab(int index);
    void tabClosed(int index);
    void tabMoved(int to, int from);
    void tabStartRename(int index);
    void tabFinishRename(void);
    void itemClosed(void);
};

#endif // SHARED_WINDOW_H
