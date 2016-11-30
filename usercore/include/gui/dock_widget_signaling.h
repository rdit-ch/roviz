#ifndef DOCKWIDGETSIGNALING_H
#define DOCKWIDGETSIGNALING_H

#include <QDockWidget>
#include <QCloseEvent>
#include <QShowEvent>

/**
 * @brief QDockWidget that emits signals
 *
 * This is a normal QDockWidget, but it emits signals when closed/shown.
 *
 * \ingroup robot_framework
 */
class DockWidgetSignaling : public QDockWidget
{
    Q_OBJECT

public:
    DockWidgetSignaling(QString title, QWidget *parent);

    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent *event) override;

signals:
    void closed(void);
    void shown(void);
};

#endif // DOCKWIDGETSIGNALING_H
